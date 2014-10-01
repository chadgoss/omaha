// Copyright 2004-2009 Google Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
// ========================================================================
//
// localization_unittest.cpp
//
// Unit test functions for Localization

#include "omaha/base/localization.h"
#include "omaha/base/string.h"
#include "omaha/base/time.h"
#include "omaha/testing/unit_test.h"

using testing::Message;

namespace omaha {

// Test out the time display functions
void LocalizationTimeTest() {
  CString time_str;

  // Lets process this a bit to give ourselves a known time.
  SYSTEMTIME temp_time;
  temp_time.wYear = 2004;
  temp_time.wMonth = 4;
  temp_time.wDayOfWeek = 1;
  temp_time.wDay = 19;
  temp_time.wHour = 19;
  temp_time.wMinute = 18;
  temp_time.wSecond = 17;
  temp_time.wMilliseconds = 16;

  time64 override_time = SystemTimeToTime64(&temp_time);

  // Useful when debugging to confirm that this worked
  SYSTEMTIME confirm = Time64ToSystemTime(override_time);
}

// Test out the numbers and display functions
void LocalizationNumberTest() {
  // Make sure we are using the normal american version
  SetLcidOverride(1033);  // the codepage for american english

  // Try some basics
  ASSERT_STREQ(Show(1), _T("1"));
  ASSERT_STREQ(Show(2), _T("2"));

  // Try some extremes
  ASSERT_STREQ(Show(0), _T("0"));
  ASSERT_STREQ(Show(kint32max), _T("2,147,483,647"));
  ASSERT_STREQ(Show(-kint32max), _T("-2,147,483,647"));
  ASSERT_STREQ(Show(kuint32max), _T("4,294,967,295"));

  // Try some doubles
  ASSERT_STREQ(Show(0.3, 0), _T("0"));
  ASSERT_STREQ(Show(0.3, 1), _T("0.3"));
  ASSERT_STREQ(Show(0.3, 2), _T("0.30"));
  ASSERT_STREQ(Show(0.3, 5), _T("0.30000"));

  // Try some with interesting rounding
  ASSERT_STREQ(Show(0.159, 0), _T("0"));
  ASSERT_STREQ(Show(0.159, 1), _T("0.1"));
  ASSERT_STREQ(Show(0.159, 2), _T("0.15"));
  ASSERT_STREQ(Show(0.159, 5), _T("0.15900"));

  // Try a nice whole number
  ASSERT_STREQ(Show(12.0, 0), _T("12"));
  ASSERT_STREQ(Show(12.0, 1), _T("12.0"));
  ASSERT_STREQ(Show(12.0, 2), _T("12.00"));
  ASSERT_STREQ(Show(12.0, 5), _T("12.00000"));
}

TEST(LocalizationTest, Localization) {
  LocalizationTimeTest();
  LocalizationNumberTest();
}

}  // namespace omaha

