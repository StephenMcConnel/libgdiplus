#ifdef WIN32
#ifndef __cplusplus
#error Please compile with a C++ compiler.
#endif
#endif

#if defined(USE_WINDOWS_GDIPLUS)
#include <Windows.h>
#include <GdiPlus.h>

#pragma comment(lib, "gdiplus.lib")
#else
#include <GdiPlusFlat.h>
#endif

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "testhelpers.h"

#ifdef USE_WINDOWS_GDIPLUS
using namespace Gdiplus;
using namespace DllExports;
#endif

static void verifyStringFormat (GpStringFormat *format, INT expectedAttributes, StringTrimming expectedTrimming)
{
	GpStatus status;
	INT flags;
	StringAlignment align;
	LANGID language;
	StringDigitSubstitute digitSubstitution;
	StringAlignment lineAlign;
	INT hotkeyPrefix;
	StringTrimming trimming;
	INT tabStopCount;
	REAL firstTabOffset;
	REAL tabStops[1];
	INT measurableCharacterRangeCount;
	
	status = GdipGetStringFormatFlags (format, &flags);
	assertEqualInt (status, Ok);
	assertEqualInt (flags, expectedAttributes);

	status = GdipGetStringFormatAlign (format, &align);
	assertEqualInt (status,Ok);
	assertEqualInt (align, StringAlignmentNear);

	status = GdipGetStringFormatDigitSubstitution (format, &language, &digitSubstitution);
	assertEqualInt (status, Ok);
	assertEqualInt (language, 0);
	assertEqualInt (align, StringDigitSubstituteUser);

	status = GdipGetStringFormatLineAlign (format, &lineAlign);
	assertEqualInt (status, Ok);
	assertEqualInt (lineAlign, StringAlignmentNear);

	status = GdipGetStringFormatHotkeyPrefix (format, &hotkeyPrefix);
	assertEqualInt (status, Ok);
	assertEqualInt (hotkeyPrefix, HotkeyPrefixNone);

	status = GdipGetStringFormatTrimming (format, &trimming);
	assertEqualInt (status, Ok);
	assertEqualInt (trimming, expectedTrimming);

	status = GdipGetStringFormatTabStopCount (format, &tabStopCount);
	assertEqualInt (status, Ok);
	assertEqualInt (tabStopCount, 0);

	status = GdipGetStringFormatTabStops (format, 0, &firstTabOffset, tabStops);
	assertEqualInt (status, Ok);
	assertEqualFloat (firstTabOffset, 0);

	status = GdipGetStringFormatMeasurableCharacterRangeCount (format, &measurableCharacterRangeCount);
	assertEqualInt (status, Ok);
	assertEqualInt (measurableCharacterRangeCount, 0);

	GdipDeleteStringFormat (format);
}

static void test_createStringFormat ()
{
	GpStatus status;
	GpStringFormat *format;

	// Positive values.
	status = GdipCreateStringFormat (10, 11, &format);
	assertEqualInt (status, Ok);
	verifyStringFormat (format, 10, StringTrimmingCharacter);

	// Zero values.
	status = GdipCreateStringFormat (0, 0, &format);
	assertEqualInt (status, Ok);
	verifyStringFormat (format, 0, StringTrimmingCharacter);

	// Negative values.
	status = GdipCreateStringFormat (-1, -2, &format);
	assertEqualInt (status, Ok);
	verifyStringFormat (format, -1, StringTrimmingCharacter);

	// Negative tests.
	status = GdipCreateStringFormat (10, 11, NULL);
	assertEqualInt (status, InvalidParameter);
}

static void test_getGenericDefault ()
{
	GpStatus status;
	GpStringFormat *format;
	
	status = GdipStringFormatGetGenericDefault (&format);
	assertEqualInt (status, Ok);
	verifyStringFormat (format, 0, StringTrimmingCharacter);

	// Negative tests.
	status = GdipStringFormatGetGenericDefault (NULL);
	assertEqualInt (status, InvalidParameter);
}

static void test_getGenericTypographic ()
{
	GpStatus status;
	GpStringFormat *format;
	
	status = GdipStringFormatGetGenericTypographic (&format);
	assertEqualInt (status, Ok);
	verifyStringFormat (format, StringFormatFlagsNoFitBlackBox | StringFormatFlagsLineLimit | StringFormatFlagsNoClip, StringTrimmingNone);

	// Negative tests.
	status = GdipStringFormatGetGenericTypographic (NULL);
	assertEqualInt (status, InvalidParameter);
}

static void test_deleteStringFormat ()
{
	GpStatus status;
	GpStringFormat *format;
	
	GdipCreateStringFormat (10, 11, &format);

	status = GdipDeleteStringFormat (format);
	assertEqualInt (status, Ok);

	// Negative tests.
	status = GdipDeleteStringFormat (NULL);
	assertEqualInt (status, InvalidParameter);
}

static void test_cloneStringFormat ()
{
	GpStatus status;
	GpStringFormat *format;
	GpStringFormat *clonedFormat;

	GdipCreateStringFormat (10, 11, &format);
	
	status = GdipCloneStringFormat (format, &clonedFormat);
	assertEqualInt (status, Ok);
	verifyStringFormat (clonedFormat, 10, StringTrimmingCharacter);

	// Negative tests.
	status = GdipCloneStringFormat (NULL, &clonedFormat);
	assertEqualInt (status, InvalidParameter);

	status = GdipCloneStringFormat (format, NULL);
	assertEqualInt (status, InvalidParameter);

	GdipDeleteStringFormat (format);
}

static void test_setStringFormatAlign ()
{
	GpStatus status;
	GpStringFormat *format;
	StringAlignment align;

	GdipCreateStringFormat (10, 11, &format);
	
	status = GdipSetStringFormatAlign (format, StringAlignmentCenter);
	assertEqualInt (status, Ok);
	
	GdipGetStringFormatAlign (format, &align);
	assertEqualInt (align, StringAlignmentCenter);

	// Negative tests.
	status = GdipSetStringFormatAlign (NULL, StringAlignmentCenter);
	assertEqualInt (status, InvalidParameter);

	status = GdipSetStringFormatAlign (format, (StringAlignment)(StringAlignmentNear - 1));
	assertEqualInt (status, InvalidParameter);

	status = GdipSetStringFormatAlign (format, (StringAlignment)(StringAlignmentFar + 1));
	assertEqualInt (status, InvalidParameter);

	GdipDeleteStringFormat (format);
}

static void test_getStringFormatAlign ()
{
	GpStatus status;
	GpStringFormat *format;
	StringAlignment align;

	GdipCreateStringFormat (10, 11, &format);

	// Negative tests.
	status = GdipGetStringFormatAlign (NULL, &align);
	assertEqualInt (status, InvalidParameter);
	
	status = GdipGetStringFormatAlign (format, NULL);
	assertEqualInt (status, InvalidParameter);

	GdipDeleteStringFormat (format);
}

static void test_setStringFormatLineAlign ()
{
	GpStatus status;
	GpStringFormat *format;
	StringAlignment lineAlign;

	GdipCreateStringFormat (10, 11, &format);
	
	status = GdipSetStringFormatLineAlign (format, StringAlignmentCenter);
	assertEqualInt (status, Ok);
	
	GdipGetStringFormatLineAlign (format, &lineAlign);
	assertEqualInt (lineAlign, StringAlignmentCenter);

	// Negative tests.
	status = GdipSetStringFormatLineAlign (NULL, StringAlignmentCenter);
	assertEqualInt (status, InvalidParameter);

	status = GdipSetStringFormatLineAlign (format, (StringAlignment)(StringAlignmentNear - 1));
	assertEqualInt (status, InvalidParameter);

	status = GdipSetStringFormatLineAlign (format, (StringAlignment)(StringAlignmentFar + 1));
	assertEqualInt (status, InvalidParameter);

	GdipDeleteStringFormat (format);
}

static void test_getStringFormatLineAlign ()
{
	GpStatus status;
	GpStringFormat *format;
	StringAlignment lineAlign;

	GdipCreateStringFormat (10, 11, &format);

	// Negative tests.
	status = GdipGetStringFormatLineAlign (NULL, &lineAlign);
	assertEqualInt (status, InvalidParameter);
	
	status = GdipGetStringFormatLineAlign (format, NULL);
	assertEqualInt (status, InvalidParameter);

	GdipDeleteStringFormat (format);
}

static void test_setStringFormatTrimming ()
{
	GpStatus status;
	GpStringFormat *format;
	StringTrimming trimming;

	GdipCreateStringFormat (10, 11, &format);
	
	status = GdipSetStringFormatTrimming (format, StringTrimmingEllipsisCharacter);
	assertEqualInt (status, Ok);
	
	GdipGetStringFormatTrimming (format, &trimming);
	assertEqualInt (trimming, StringTrimmingEllipsisCharacter);

	// Negative tests.
	status = GdipSetStringFormatTrimming (NULL, StringTrimmingEllipsisCharacter);
	assertEqualInt (status, InvalidParameter);

	status = GdipSetStringFormatTrimming (format, (StringTrimming)(StringTrimmingNone - 1));
	assertEqualInt (status, InvalidParameter);

	status = GdipSetStringFormatTrimming (format, (StringTrimming)(StringTrimmingEllipsisPath + 1));
	assertEqualInt (status, InvalidParameter);

	GdipDeleteStringFormat (format);
}

static void test_getStringFormatTrimming ()
{
	GpStatus status;
	GpStringFormat *format;
	StringTrimming trimming;

	GdipCreateStringFormat (10, 11, &format);

	// Negative tests.
	status = GdipGetStringFormatTrimming (NULL, &trimming);
	assertEqualInt (status, InvalidParameter);
	
	status = GdipGetStringFormatTrimming (format, NULL);
	assertEqualInt (status, InvalidParameter);

	GdipDeleteStringFormat (format);
}

static void test_setStringFormatHotkeyPrefix ()
{
	GpStatus status;
	GpStringFormat *format;
	INT hotkeyPrefix;

	GdipCreateStringFormat (10, 11, &format);
	
	status = GdipSetStringFormatHotkeyPrefix (format, HotkeyPrefixShow);
	assertEqualInt (status, Ok);
	
	GdipGetStringFormatHotkeyPrefix (format, &hotkeyPrefix);
	assertEqualInt (hotkeyPrefix, HotkeyPrefixShow);

	// Negative tests.
	status = GdipSetStringFormatHotkeyPrefix (NULL, HotkeyPrefixNone);
	assertEqualInt (status, InvalidParameter);

	status = GdipSetStringFormatHotkeyPrefix (format, (HotkeyPrefix)(HotkeyPrefixNone - 1));
	assertEqualInt (status, InvalidParameter);

	status = GdipSetStringFormatHotkeyPrefix (format, (HotkeyPrefix)(HotkeyPrefixHide + 1));
	assertEqualInt (status, InvalidParameter);

	GdipDeleteStringFormat (format);
}

static void test_getStringFormatHotkeyPrefix ()
{
	GpStatus status;
	GpStringFormat *format;
	INT hotkeyPrefix;

	GdipCreateStringFormat (10, 11, &format);

	// Negative tests.
	status = GdipGetStringFormatHotkeyPrefix (NULL, &hotkeyPrefix);
	assertEqualInt (status, InvalidParameter);
	
	status = GdipGetStringFormatHotkeyPrefix (format, NULL);
	assertEqualInt (status, InvalidParameter);

	GdipDeleteStringFormat (format);
}

static void test_setStringFormatTabStops ()
{
	GpStatus status;
	GpStringFormat *format;
	REAL firstTabOffset;
	REAL tabStops[4] = {1, 0, 2, 3};
	REAL oneTabStop[1] = {0};
	REAL negativeValueInTabStops[4] = {1, -1};
	REAL formatTabStops[4];

	GdipCreateStringFormat (10, 11, &format);
	
	// Count of 4.
	status = GdipSetStringFormatTabStops (format, 10, 4, tabStops);
	assertEqualInt (status, Ok);
	
	GdipGetStringFormatTabStops (format, 4, &firstTabOffset, formatTabStops);
	assertEqualFloat (firstTabOffset, 10);
	assertEqualFloat (formatTabStops[0], 1);
	assertEqualFloat (formatTabStops[1], 0);
	assertEqualFloat (formatTabStops[2], 2);
	assertEqualFloat (formatTabStops[3], 3);

	// Count of 1.
	status = GdipSetStringFormatTabStops (format, 0, 1, oneTabStop);
	assertEqualInt (status, Ok);
	
	GdipGetStringFormatTabStops (format, 1, &firstTabOffset, formatTabStops);
	assertEqualFloat (firstTabOffset, 0);
	assertEqualFloat (formatTabStops[0], 0);

	// Count of 0.
	status = GdipSetStringFormatTabStops (format, 10, 0, oneTabStop);
	assertEqualInt (status, Ok);
	
	GdipGetStringFormatTabStops (format, 1, &firstTabOffset, formatTabStops);
	assertEqualFloat (firstTabOffset, 0);
	assertEqualFloat (formatTabStops[0], 0);

	// Count of -1.
	status = GdipSetStringFormatTabStops (format, 10, -1, oneTabStop);
	assertEqualInt (status, Ok);
	
	GdipGetStringFormatTabStops (format, 1, &firstTabOffset, formatTabStops);
	assertEqualFloat (firstTabOffset, 0);
	assertEqualFloat (formatTabStops[0], 0);

	// Count of 0, invalid first tab offset.
	status = GdipSetStringFormatTabStops (format, -1, 0, oneTabStop);
	assertEqualInt (status, Ok);
	
	GdipGetStringFormatTabStops (format, 1, &firstTabOffset, formatTabStops);
	assertEqualFloat (firstTabOffset, 0);
	assertEqualFloat (formatTabStops[0], 0);

	// Negative tests,
	status = GdipSetStringFormatTabStops (NULL, 10, -1, oneTabStop);
	assertEqualInt (status, InvalidParameter);

	status = GdipSetStringFormatTabStops (format, 10, -1, NULL);
	assertEqualInt (status, InvalidParameter);

	status = GdipSetStringFormatTabStops (format, -1, 10, oneTabStop);
	assertEqualInt (status, NotImplemented);

	// Negative value in tab stops.
	formatTabStops[0] = 10;
	status = GdipSetStringFormatTabStops (format, 40, 4, negativeValueInTabStops);
	assertEqualInt (status, NotImplemented);

	status = GdipGetStringFormatTabStops (format, 4, &firstTabOffset, formatTabStops);
	assertEqualInt (status, Ok);
	assertEqualFloat (firstTabOffset, 0);
	assertEqualFloat (formatTabStops[0], 0);

	GdipDeleteStringFormat (format);
}

static void test_getStringFormatTabStops ()
{
	GpStatus status;
	GpStringFormat *format;
	REAL firstTabOffset = 10;
	REAL tabStops[4] = {1, 2, 3, 4};
	REAL formatTabStops[5] = {-1, -2, -3, -4, -5};

	GdipCreateStringFormat (10, 11, &format);

	// Count of 0 - still overwrites the firstTabOffset value.
	status = GdipGetStringFormatTabStops (format, 0, &firstTabOffset, formatTabStops);
	assertEqualInt (status, Ok);
	assertEqualFloat (firstTabOffset, 0);

	// Count less than the number of tab stops.
	GdipSetStringFormatTabStops (format, 10, 4, tabStops);

	status = GdipGetStringFormatTabStops (format, 2, &firstTabOffset, formatTabStops);
	assertEqualInt (status, Ok);
	assertEqualFloat (firstTabOffset, 10);
	assertEqualFloat (formatTabStops[0], 1);
	assertEqualFloat (formatTabStops[1], 2);
	assertEqualFloat (formatTabStops[2], -3);
	assertEqualFloat (formatTabStops[3], -4);
	assertEqualFloat (formatTabStops[4], -5);

	// Count greater than the number of tab stops.
	GdipSetStringFormatTabStops (format, 10, 4, tabStops);

	status = GdipGetStringFormatTabStops (format, 5, &firstTabOffset, formatTabStops);
	assertEqualInt (status, Ok);
	assertEqualFloat (firstTabOffset, 10);
	assertEqualFloat (formatTabStops[0], 1);
	assertEqualFloat (formatTabStops[1], 2);
	assertEqualFloat (formatTabStops[2], 3);
	assertEqualFloat (formatTabStops[3], 4);
	assertEqualFloat (formatTabStops[4], -5);
	
	// Negative tests,
	status = GdipGetStringFormatTabStops (NULL, 0, &firstTabOffset, formatTabStops);
	assertEqualInt (status, InvalidParameter);

	status = GdipGetStringFormatTabStops (format, 0, NULL, formatTabStops);
	assertEqualInt (status, InvalidParameter);

	status = GdipGetStringFormatTabStops (format, 0, &firstTabOffset, NULL);
	assertEqualInt (status, InvalidParameter);

	// This causes GDI+ to crash.
#if !defined(_WIN32)
	status = GdipGetStringFormatTabStops (format, -1, &firstTabOffset, formatTabStops);
	assertEqualInt (status, InvalidParameter);
#endif

	GdipDeleteStringFormat (format);
}

static void test_getStringFormatTabStopCount ()
{
	GpStatus status;
	GpStringFormat *format;
	INT tabStopCount;

	GdipCreateStringFormat (10, 11, &format);
	
	// Negative tests.
	status = GdipGetStringFormatTabStopCount (NULL, &tabStopCount);
	assertEqualInt (status, InvalidParameter);

	status = GdipGetStringFormatTabStopCount (format, NULL);
	assertEqualInt (status, InvalidParameter);

	GdipDeleteStringFormat (format);
}

static void test_setStringFormatDigitSubstitution ()
{
	GpStatus status;
	GpStringFormat *format;
	LANGID language;
	StringDigitSubstitute substitute;

	GdipCreateStringFormat (10, 11, &format);

	// Valid value.
	status = GdipSetStringFormatDigitSubstitution (format, 10, StringDigitSubstituteNational);
	assertEqualInt (status, Ok);

	GdipGetStringFormatDigitSubstitution (format, &language, &substitute);
	assertEqualInt (language, 10);
	assertEqualInt (substitute, StringDigitSubstituteNational);

	// Invalid value - negative.
	status = GdipSetStringFormatDigitSubstitution (format, 0, (StringDigitSubstitute)(StringDigitSubstituteUser - 1));
	assertEqualInt (status, Ok);

	GdipGetStringFormatDigitSubstitution (format, &language, &substitute);
	assertEqualInt (language, 0);
	assertEqualInt (substitute, (StringDigitSubstitute)(StringDigitSubstituteUser - 1));

	// Invalid value - positive.
	status = GdipSetStringFormatDigitSubstitution (format, 0, (StringDigitSubstitute)(StringDigitSubstituteTraditional + 1));
	assertEqualInt (status, Ok);

	GdipGetStringFormatDigitSubstitution (format, &language, &substitute);
	assertEqualInt (language, 0);
	assertEqualInt (substitute, (StringDigitSubstitute)(StringDigitSubstituteTraditional + 1));
	
	// Negative tests.
	status = GdipSetStringFormatDigitSubstitution (NULL, 0, StringDigitSubstituteNational);
	assertEqualInt (status, InvalidParameter);

	GdipDeleteStringFormat (format);
}

static void test_getStringFormatDigitSubstitution ()
{
	GpStatus status;
	GpStringFormat *format;
	LANGID language;
	StringDigitSubstitute substitute;

	GdipCreateStringFormat (10, 11, &format);

	// Language null.
	status = GdipGetStringFormatDigitSubstitution (format, &language, NULL);
	assertEqualInt (status, Ok);
	assertEqualInt (language, 0);

	// Substitution null.
	status = GdipGetStringFormatDigitSubstitution (format, NULL, &substitute);
	assertEqualInt (status, Ok);
	assertEqualInt (substitute, StringDigitSubstituteUser);

	// Both null.
	status = GdipGetStringFormatDigitSubstitution (format, NULL, NULL);
	assertEqualInt (status, Ok);

	// Negative tests.
	status = GdipGetStringFormatDigitSubstitution (NULL, &language, &substitute);
	assertEqualInt (status, InvalidParameter);

	GdipDeleteStringFormat (format);
}

static void test_getStringFormatMeasurableCharacterRangeCount ()
{
	GpStatus status;
	GpStringFormat *format;
	INT measurableCharacterRangeCount;

	GdipCreateStringFormat (10, 11, &format);
	
	// Negative tests.
	status = GdipGetStringFormatMeasurableCharacterRangeCount (NULL, &measurableCharacterRangeCount);
	assertEqualInt (status, InvalidParameter);

	status = GdipGetStringFormatMeasurableCharacterRangeCount (format, NULL);
	assertEqualInt (status, InvalidParameter);

	GdipDeleteStringFormat (format);
}

static void test_setStringFormatMeasurableCharacterRanges ()
{
	GpStatus status;
	GpStringFormat *format;
	CharacterRange ranges[3];
	INT measurableCharacterRangeCount;
	
	GdipCreateStringFormat (10, 11, &format);

	// Count of 1.
	status = GdipSetStringFormatMeasurableCharacterRanges (format, 1, ranges);
	assertEqualInt (status, Ok);

	GdipGetStringFormatMeasurableCharacterRangeCount (format, &measurableCharacterRangeCount);
	assertEqualInt (measurableCharacterRangeCount, 1);

	// Count of 0.
	GdipSetStringFormatMeasurableCharacterRanges (format, 3, ranges);

	status = GdipSetStringFormatMeasurableCharacterRanges (format, 0, ranges);
	assertEqualInt (status, Ok);

	GdipGetStringFormatMeasurableCharacterRangeCount (format, &measurableCharacterRangeCount);
	assertEqualInt (measurableCharacterRangeCount, 0);

	// Count of -1.
	GdipSetStringFormatMeasurableCharacterRanges (format, 3, ranges);

	status = GdipSetStringFormatMeasurableCharacterRanges (format, -1, ranges);
	assertEqualInt (status, Ok);

	GdipGetStringFormatMeasurableCharacterRangeCount (format, &measurableCharacterRangeCount);
	assertEqualInt (measurableCharacterRangeCount, 0);
	
	// Negative tests.
	status = GdipSetStringFormatMeasurableCharacterRanges (NULL, 0, ranges);
	assertEqualInt (status, InvalidParameter);

	status = GdipSetStringFormatMeasurableCharacterRanges (format, 0, NULL);
	assertEqualInt (status, InvalidParameter);

	status = GdipSetStringFormatMeasurableCharacterRanges (format, 33, ranges);
	assertEqualInt (status, ValueOverflow);

	GdipDeleteStringFormat (format);
}

int
main (int argc, char**argv)
{
	GdiplusStartupInput gdiplusStartupInput;
	ULONG_PTR gdiplusToken;
	GdiplusStartup (&gdiplusToken, &gdiplusStartupInput, NULL);

	test_createStringFormat ();
	test_getGenericDefault ();
	test_getGenericTypographic ();
	test_deleteStringFormat ();
	test_cloneStringFormat ();
	test_setStringFormatAlign ();
	test_getStringFormatAlign ();
	test_setStringFormatLineAlign ();
	test_getStringFormatLineAlign ();
	test_setStringFormatTrimming ();
	test_getStringFormatTrimming ();
	test_setStringFormatHotkeyPrefix ();
	test_getStringFormatHotkeyPrefix ();
	test_setStringFormatTabStops ();
	test_getStringFormatTabStops ();
	test_getStringFormatTabStopCount ();
	test_setStringFormatDigitSubstitution ();
	test_getStringFormatDigitSubstitution ();
	test_getStringFormatMeasurableCharacterRangeCount ();
	test_setStringFormatMeasurableCharacterRanges ();

	GdiplusShutdown (gdiplusToken);
	return 0;
}
