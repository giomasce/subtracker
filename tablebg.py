#!/usr/bin/env python2
# -*- coding: utf-8 -*-

import cv2
import numpy

class TableBackgroundEstimationSettings:

    def __init__(self, controls):
        # TODO: initial_value
        self.alpha = controls.trackbar("alpha", 0.005, 0.0, 0.1, 0.001).value
        self.var_alpha = controls.trackbar("var alpha", 0.005, 0.0, 0.1, 0.001).value

class TableBackgroundEstimation:

    def __init__(self):
        self.mean = None
        self.variance = None

class FrameTableAnalysis:
    pass

def weighted_update(alpha, prev, curr):
    return (1 - alpha) * prev + alpha * curr

def initial_estimation(warped_frame, settings):
    # Our initial best estimate for the table is the first frame that
    # we see
    estimation = TableBackgroundEstimation()
    estimation.mean = warped_frame.copy()

    # But this is going to be terribly unreliable, so we put high
    # variance (FIXME: is 1000.0 high enough? Or too much?)
    estimation.variance = []
    for ch1 in xrange(3):
        estimation.variance.append(cv2.split(1000.0 * numpy.ones_like(warped_frame)))

    return estimation

def update_estimation(prev, warped_frame, settings):
    estimation = TableBackgroundEstimation()

    estimation.mean = weighted_update(settings.alpha, prev.mean, warped_frame)

    diff = warped_frame - estimation.mean
    diff_channels = cv2.split(diff)

    # TODO: save half the computations as variance is symmetric
    estimation.variance = [[None] * 3, [None] * 3, [None] * 3]
    for ch1 in xrange(3):
        for ch2 in xrange(3):
            scatter = cv2.multiply(diff_channels[ch1], diff_channels[ch2])
            prev_var = prev.variance[ch1][ch2]
            estimation.variance[ch1][ch2] = weighted_update(settings.var_alpha, prev_var, scatter)

    return estimation

def estimate_table_background(prev, warped_frame, settings, controls):
    if prev is not None:
        estimation = update_estimation(prev, warped_frame, settings)
    else:
        estimation = initial_estimation(warped_frame, settings)

    controls.show("mean", estimation.mean)
    controls.show("covar B-G", estimation.variance[0][1])
    return estimation