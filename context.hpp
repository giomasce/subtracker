#ifndef CONTEXT_HPP_
#define CONTEXT_HPP_

#include <deque>

#include <opencv2/core/core.hpp>

#include "control.hpp"
#include "framereader_structs.hpp"
#include "subotto_tracking.hpp"
#include "analysis.hpp"
#include "blobs_tracker.hpp"

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
	int local_maxima_limit = 5;
	float local_maxima_min_distance = 0.10f;

  FrameSettings(Mat ref_frame, Mat ref_mask);

};

class FrameAnalysis {

public:

  // Global frame data
  Mat frame;
  int frame_num;
  time_point< video_clock > timestamp;
  FrameSettings frame_settings;
  control_panel_t &panel;

  // Table tracking
  table_tracking_status_t table_tracking_status;
  Mat table_transform;
  Mat table_frame;

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

  // Search blobs
  vector< Blob > blobs;

  FrameAnalysis(Mat frame, int frame_num, time_point< video_clock > timestamp, FrameSettings frame_settings, control_panel_t &panel, Size table_frame_size);

  void setup_from_prev_table_tracking(const FrameAnalysis &prev_frame_analysis);
  void track_table();
  void warp_table_frame();

  void setup_from_prev_table_analysis(const FrameAnalysis & prev_frame_analysis);
  void analyze_table();
  void analyze_ball();
  void analyze_foosmen();
  void update_table_description();
  void update_corrected_variance();

  void search_blobs();

};

class SubtrackerContext {

public:

  int last_frame_num;
  control_panel_t &panel;
  FrameSettings frame_settings;

  FrameAnalysis *frame_analysis;
  FrameAnalysis *prev_frame_analysis;

  SubtrackerContext(Mat ref_frame, Mat ref_mask, control_panel_t &panel);
  ~SubtrackerContext();

  void feed(Mat frame, time_point< video_clock > timestamp);
  void do_table_tracking();
  void do_analysis();
  void do_blob_search();

};

#endif