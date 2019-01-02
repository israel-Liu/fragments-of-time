#!/usr/bin/env python
# Copyright (c) 2018 The Zoom Authors. All rights reserved.
# Use of this source code is governed by a BSD-style license that can be
# found in the LICENSE file.

"""
Tool to perform checkouts in one easy command line!

Usage:
  pull <config> [--property=value [--property2=value2 ...]]

This script will use git command "git fetch -p" and "git rebase" to
update all branches to have the latest changes from their upstreams.

The branches .git contain in the folder which is same level with this.
"""

import argparse
import json
import optparse
import os
import pipes
import subprocess
import sys
import textwrap

import git_common as git

from distutils import spawn

SCRIPT_PATH = os.path.abspath(os.path.join(os.path.dirname("__file__"), os.path.pardir))
      
def main(args = None):
  for folder in os.listdir(SCRIPT_PATH):
    folder = os.path.join(SCRIPT_PATH, folder)
    for git_folder in os.listdir(folder):
      if git_folder == '.git':
        os.chdir(folder)
        git.run('fetch', '-p')
        cur_branch = git.current_branch()
        git.run('rebase', 'origin/master', cur_branch)
        break

  print "pull succeed"
  return 0

if __name__ == '__main__':
  try:
    sys.exit(main())
  except KeyboardInterrupt:
    sys.stderr.write('interrupted\n')
    sys.exit(1)
