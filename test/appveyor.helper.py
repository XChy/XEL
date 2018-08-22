#!/usr/bin/env python
# Build the project on AppVeyor.

import os
from subprocess import check_call

print "hello from appveyor.helper.py"

config = os.environ['CONFIG']
path = os.environ['PATH']
cmake_command = ['cmake', '-DFMT_PEDANTIC=ON', '-DCMAKE_BUILD_TYPE=' + config]

os.environ['PATH'] = r'C:\Program Files (x86)\MSBuild\14.0\Bin;' + path
build_command = ['msbuild', '/m:4', '/p:Config=' + config, 'foo.sln']
#test_command = ['msbuild', 'RUN_TESTS.vcxproj']

check_call(cmake_command)
check_call(build_command)
#check_call(test_command)