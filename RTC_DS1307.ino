#include "RTClib.h" // DS1307 RTC 라이브러리

RTC_DS1307 rtc;  // rtc 객체

// 월요일~일요일 배열값
char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

void setup () {
  Serial.begin(9600);

  if (! rtc.begin()) {  // RTC 연결 확인
    Serial.println("Couldn't find RTC");
    Serial.flush();
    abort();
  }

  if (! rtc.isrunning()) {  // RTC모듈 작동 확인
    Serial.println("RTC is NOT running, let's set the time!");
    
    // 사용자의 컴퓨터 시계의 날짜와 시간을 가져와서 RTC의 시간으로 설정하는 명령어입니다.
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    
    // 수동으로 RTC시간을 조정하려면 아래와 같이 하면 됩니다.
    // January 21, 2014 at 3am 으로 설정하고 싶을 경우:
    // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
  }

}

void loop () {
  // RTC의 시간을 읽습니다.
    DateTime now = rtc.now();

    Serial.print(now.year(), DEC);
    Serial.print('/');
    Serial.print(now.month(), DEC);
    Serial.print('/');
    Serial.print(now.day(), DEC);
    Serial.print(" (");
    Serial.print(daysOfTheWeek[now.dayOfTheWeek()]);
    Serial.print(") ");
    Serial.print(now.hour(), DEC);
    Serial.print(':');
    Serial.print(now.minute(), DEC);
    Serial.print(':');
    Serial.print(now.second(), DEC);
    Serial.println();

    Serial.print(" since midnight 1/1/1970 = ");
    Serial.print(now.unixtime()); // 1970년 1월 1일 이후의 초를 계산하는 unixtime
    Serial.print("s = ");
    Serial.print(now.unixtime() / 86400L); // 하루는 86400초, 1970년 이후로 며칠이 지났는지 계산
    Serial.println("d");

    // 지금으로부터 7 days, 12 hours, 30 minutes, and 6 seconds 가 지났을 때의 미래 시간
    DateTime future (now + TimeSpan(7,12,30,6));

    Serial.print(" now + 7d + 12h + 30m + 6s: ");
    Serial.print(future.year(), DEC);
    Serial.print('/');
    Serial.print(future.month(), DEC);
    Serial.print('/');
    Serial.print(future.day(), DEC);
    Serial.print(' ');
    Serial.print(future.hour(), DEC);
    Serial.print(':');
    Serial.print(future.minute(), DEC);
    Serial.print(':');
    Serial.print(future.second(), DEC);
    Serial.println();

    Serial.println();
    delay(3000);
}
