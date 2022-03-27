#
# Copyright 2021 Xilinx, Inc.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#

export XCLBIN_PATH=/lib/firmware/xilinx/kv260-vvas-sms/kv260-vvas-sms.xclbin

# Set alpha plane.
modetest -M xlnx -w 40:alpha:0

# Force DP resolution to 1080P and display diagonal test pattern
modetest -M xlnx -s 43@41:1920x1080-60@AR24 -P 39@41:1920x1080@NV12  -w 40:alpha:0 &

