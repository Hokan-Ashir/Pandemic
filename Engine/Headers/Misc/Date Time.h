/******************************************************************************
 * Copyright (c) Grzegorz Slazinski. All Rights Reserved.                     *
 * Esenthel Engine (http://www.esenthel.com) header file.                     *
/******************************************************************************

   Use 'DateTime' to handle time and date information.

/******************************************************************************/
struct DateTime
{
   Byte second, // 0..59
        minute, // 0..59
        hour  , // 0..23
        day   , // 1..31
        month ; // 1..12
   Int  year  ;

   // get
   Bool valid     (                         )C; // if  current date time is valid
   Int  days      (                         )C; // get    days since 1 January 0 year
   Long seconds   (                         )C; // get seconds since 1 January 0 year
   Str  asText    (Bool include_seconds=true)C; // get date in text      format "YYYY-MM-DD HH:MM:SS"
   Str  asFileName(Bool include_seconds=true)C; // get date in file name format "YYYY-MM-DD HH,MM,SS"

   // set
   DateTime& zero       (        ); // set date and time to zero
   DateTime& getLocal   (        ); // set from current DateTime (local time zone)
   DateTime& getUTC     (        ); // set from current DateTime (UTC   time zone)
   DateTime& incMonth   (        ); // increase by 1 month
   DateTime& decMonth   (        ); // decrease by 1 month
   DateTime& incDay     (        ); // increase by 1 day
   DateTime& decDay     (        ); // decrease by 1 day
   DateTime& incHour    (        ); // increase by 1 hour
   DateTime& decHour    (        ); // decrease by 1 hour
   DateTime& incMinute  (        ); // increase by 1 minute
   DateTime& decMinute  (        ); // decrease by 1 minute
   DateTime& incSecond  (        ); // increase by 1 second
   DateTime& decSecond  (        ); // decrease by 1 second
   DateTime& toUTC      (        ); // convert from local to UTC   time zone
   DateTime& toLocal    (        ); // convert from UTC   to local time zone
   DateTime& fromSeconds(  Long s); // set date from seconds since 1 January 0 year
   DateTime& fromText   (C Str &t); // set date from text format "YYYY-MM-DD HH:MM:SS" ("YYYY-MM-DD HH:MM" format is also supported), 'zero' method is called on fail

   // io
   void save(File &f)C;
   void load(File &f) ;
};
/******************************************************************************/
// compare
       Int  Compare   (C DateTime &d0, C DateTime &d1             ); // compare
       Int  Compare   (C DateTime &d0, C DateTime &d1, Int epsilon); // compare using 'epsilon' for seconds tolerance
inline Bool operator==(C DateTime &d0, C DateTime &d1             ) {return Compare(d0, d1)==0;} // if equal
inline Bool operator!=(C DateTime &d0, C DateTime &d1             ) {return Compare(d0, d1)!=0;} // if not equal
inline Bool operator>=(C DateTime &d0, C DateTime &d1             ) {return Compare(d0, d1)>=0;} // if greater or equal
inline Bool operator<=(C DateTime &d0, C DateTime &d1             ) {return Compare(d0, d1)<=0;} // if smaller or equal
inline Bool operator> (C DateTime &d0, C DateTime &d1             ) {return Compare(d0, d1)> 0;} // if greater
inline Bool operator< (C DateTime &d0, C DateTime &d1             ) {return Compare(d0, d1)< 0;} // if smaller

Long operator+(C DateTime &d0, C DateTime &d1); // return sum             of DateTime seconds
Long operator-(C DateTime &d0, C DateTime &d1); // return difference between DateTime seconds

Bool LeapYear (Int  year                          ); // check if 'year' is a leap year
Int  MonthDays(Int  month                         ); // return number of days in a month, 'month'=1..12, -1 on fail
Int  MonthDays(Int  month  , Int  year            ); // return number of days in a month, 'month'=1..12, -1 on fail, this makes additional check to the 'year' if it's a leap year
Str  TimeText (Long seconds, Bool short_names=true); // convert seconds to string, Sample Usage: TimeText(61) -> "1m 1s"
/******************************************************************************/
