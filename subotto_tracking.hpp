#ifndef SUBOTTODETECTOR_H_
#define SUBOTTODETECTOR_H_

#include "subotto_metrics.hpp"
#include "framereader.hpp"

#include <opencv2/core/core.hpp>
#include <opencv2/videostab/videostab.hpp>

#include <memory>

struct SubottoReference {
	cv::Mat image;
	cv::Mat mask;
	SubottoReferenceMetrics metrics;
};

struct table_detection_params_t {
	int reference_features_per_level = 300;
	int reference_features_levels = 3;

	int frame_features_per_level = 500;
	int frame_features_levels = 3;

	int features_knn = 2;

	float coarse_ransac_threshold = 20.f;
	float coarse_ransac_outliers_ratio = 0.5f;

	int optical_flow_features;
	float optical_flow_ransac_threshold = 1.0f;

	SubottoReference reference;
};

struct table_following_params_t {
	int optical_flow_features = 100;
	float optical_flow_ransac_threshold = 1.0f;

	cv::Size optical_flow_size {128, 64};

	SubottoReference reference;
};

struct table_tracking_params_t {
	table_detection_params_t detection_params;
	table_following_params_t following_params;

	int detection_every_frames = 120;
	float near_transform_alpha = 0.25f;
};

struct table_tracking_status_t {
	cv::Mat near_transform;
	int frames_to_next_detection;
};

struct table_tracking_t {
	frame_info frameInfo;
	cv::Mat frame;
	cv::Mat transform;
};

Mat detect_table(Mat frame, table_detection_params_t params);
Mat follow_table(Mat frame, Mat previous_transform, table_following_params_t params);

void init_table_tracking(table_tracking_status_t& status, table_tracking_params_t params);
Mat track_table(Mat frame, table_tracking_status_t& status, table_tracking_params_t params);

void drawSubottoBorders(cv::Mat& outImage, const cv::Mat& transform, cv::Scalar color);

#endif /* SUBOTTODETECTOR_H_ */
