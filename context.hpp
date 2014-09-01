#ifndef CONTEXT_HPP_
#define CONTEXT_HPP_

#include <deque>

#include <opencv2/core/core.hpp>

#include "control.hpp"
#include "framereader_structs.hpp"
#include "tracking_types.hpp"
#include "analysis.hpp"
#include "spots_tracker.hpp"

using namespace std;
using namespace cv;

class FrameSettings {

public:

  table_tracking_params_t table_tracking_params;
  SubottoReference reference;
  Size table_frame_size;
  SubottoMetrics table_metrics;
  foosmen_params_t foosmen_params;
  FoosmenMetrics foosmen_metrics;
  int local_maxima_limit;
  float local_maxima_min_distance;

  FrameSettings(Mat ref_frame, Mat ref_mask);

};

class FrameAnalysis {

public:

  // Global frame data
  Mat frame;
  int frame_num;
  time_point< video_clock > timestamp;
  time_point< system_clock > playback_time;
  FrameSettings frame_settings;
  control_panel_t &panel;

  // Table tracking
  table_tracking_status_t table_tracking_status;
  Mat table_transform;
  Mat table_frame;
  bool feature_matching_used;
  Mat follow_table_before;
  Mat detect_table_matches;
  Mat detect_table_after_matching;

  // Table analysis
  TableDescription table_description;
  TableAnalysis table_analysis;

  // Ball analysis
  BallDescription ball_description;
  BallAnalysis ball_analysis;
  Mat ball_density;

  // Foosmen analysis
  FoosmenBarMetrics foosmen_bars_metrics[BARS][2];
  FoosmenBarAnalysis foosmen_bars_analysis[BARS][2];
  float bars_shift[BARS][2];
  float bars_rot[BARS][2];

  // Search spots
  vector< Spot > spots;

  // Final position
  float ball_pos_x, ball_pos_y;
  bool ball_is_present;
  Mat ball_display;
  Mat foosmen_display;

  FrameAnalysis(Mat frame, int frame_num, time_point< video_clock > timestamp, time_point< system_clock > playback_time, FrameSettings frame_settings, control_panel_t &panel);

  void setup_from_prev_table_tracking(const FrameAnalysis &prev_frame_analysis);
  void track_table();
  void warp_table_frame();

  void setup_from_prev_table_analysis(const FrameAnalysis & prev_frame_analysis);
  void analyze_table();
  void analyze_ball();
  void analyze_foosmen();
  void update_table_description();
  void update_corrected_variance();

  void search_spots();

  string get_csv_line();
  void draw_ball_display();
  void draw_foosmen_display();
  void show_all_displays();

};

class SubtrackerContext {

public:

  int last_frame_num;
  control_panel_t &panel;
  FrameSettings frame_settings;

  FrameAnalysis *frame_analysis;
  FrameAnalysis *prev_frame_analysis;
  deque< FrameAnalysis > past_frames;
  deque< FrameAnalysis > ready_frames;

  // Spots tracking
  SpotsTracker spots_tracker;
  int spots_timeline_span;

  SubtrackerContext(Mat ref_frame, Mat ref_mask, control_panel_t &panel);
  ~SubtrackerContext();

  void feed(Mat frame, time_point< video_clock > timestamp, time_point< system_clock > playback_time);
  FrameAnalysis *get_processed_frame();

  void do_table_tracking();
  void do_analysis();
  void do_spot_search();
  void do_spots_tracking();

};

#endif
