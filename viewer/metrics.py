#!/usr/bin/env python2
# -*- coding: utf-8 -*-

# Distance values are in meters
FIELD_WIDTH = 1.135
FIELD_HEIGHT = 0.7

BALL_DIAMETER = 0.035

ROD_DIAMETER = 0.015
ROD_HEIGHT = 0.085
ROD_DISTANCE = 0.15
ROD_COLORS = ['red', 'blue']
ROD_CONFIGURATION = [(1, 0.0, 0),
                     (2, 0.24, 0),
                     (3, 0.21, 1),
                     (5, 0.12, 0),
                     (5, 0.12, 1),
                     (3, 0.21, 0),
                     (2, 0.24, 1),
                     (1, 0.0, 1)]
ROD_NUMBER = len(ROD_CONFIGURATION)

FOOSMAN_WIDTH = 0.03
FOOSMAN_HEAD_HEIGHT = 0.02
FOOSMAN_FEET_HEIGHT = 0.08

# Colors
BALL_COLOR = (0.85, 0.85, 0.85)
FIELD_COLOR = (0.2, 0.7, 0.2)
ROD_COLOR = (0.6, 0.6, 0.6)
FOOSMEN_COLORS = [(0.65, 0.10, 0.05),
                  (0.05, 0.25, 0.50)]

# Private for viewer
CYLINDER_FACTOR = 10.0
