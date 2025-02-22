#!/bin/bash -e
# Copyright (C) 2022 The Android Open Source Project
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#       http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

# Script used as --workspace_status_command.
# Must execute at the root of workspace.
# https://docs.bazel.build/versions/main/command-line-reference.html#flag--workspace_status_command

if [[ ! -f "WORKSPACE" ]]; then
  echo "ERROR: workspace_status.sh must be executed at the root of Bazel workspace." >&2
  exit 1
fi

KERNEL_DIR=$(readlink -f ".source_date_epoch_dir")

# Find scripts/setlocalversion.
# .source_date_epoch_dir should be where KERNEL_DIR is. Look for setlocalversion there.
SETLOCALVERSION=""
if [[ -n "$KERNEL_DIR" ]] && [[ -x "$KERNEL_DIR/scripts/setlocalversion" ]]; then
  SETLOCALVERSION=$(readlink -f "$KERNEL_DIR/scripts/setlocalversion")
fi

STABLE_SCMVERSION=
if [[ -n "$SETLOCALVERSION" ]] && [[ -n "$KERNEL_DIR" ]] && [[ -d "$KERNEL_DIR" ]]; then
  WORKING_DIR=build/kernel/kleaf/workspace_status_dir
  STABLE_SCMVERSION=$(cd "$WORKING_DIR" && "$SETLOCALVERSION" "$KERNEL_DIR")
fi

STABLE_SOURCE_DATE_EPOCH=${SOURCE_DATE_EPOCH:-0}
if [[ -n "$KERNEL_DIR" ]] && [[ -d "$KERNEL_DIR" ]]; then
  # Use "git" from the environment.
  STABLE_SOURCE_DATE_EPOCH=${SOURCE_DATE_EPOCH:-$(git -C "$KERNEL_DIR" log -1 --pretty=%ct)}
fi

echo "STABLE_SCMVERSION $STABLE_SCMVERSION"
echo "STABLE_SOURCE_DATE_EPOCH $STABLE_SOURCE_DATE_EPOCH"

