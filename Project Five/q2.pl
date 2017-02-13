key( 1, 'January',   jan, 6, 1). 
key( 2, 'February',  feb, 2, 1). 
key( 3, 'March',     mar, 2, 0). 
key( 4, 'April',     apr, 5, 0). 
key( 5, 'May',       may, 0, 0). 
key( 6, 'June',      jun, 3, 0). 
key( 7, 'July',      jul, 5, 0). 
key( 8, 'August',    aug, 1, 0). 
key( 9, 'September', sep, 4, 0). 
key(10, 'October',   oct, 6, 0). 
key(11, 'November',  nov, 2, 0). 
key(12, 'December',  dec, 4, 0). 
month_name(Number, Name) :- key(Number, Name, _, _, _). 

 
dow(0, 'Sunday',    sun). 
dow(1, 'Monday',    mon). 
dow(2, 'Tuesday',   tue). 
dow(3, 'Wednesday', wed). 
dow(4, 'Thursday',  thu). 
dow(5, 'Friday',    fri). 
dow(6, 'Saturday',  sat). 


day_of_week(Year,Month,Day, DayOfWeek) :- 
        Temp is Year // 100, 
        YearInTemp is Year - Temp * 100, 
        (  key(Month, _, _, Key, LeapC) 
        ;  key(_, Month, _, Key, LeapC) 
        ;  key(_, _, Month, Key, LeapC) 
        ), !, 
        DOW0 is (Temp * 5 + Temp // 4 + 
                 YearInTemp + YearInTemp // 4 + 
                 Day + Key) mod 7, 
        ( leapYear(Year) -> DOW is DOW0 - LeapC ; DOW is DOW0 ), 
        dow(DOW, DayOfWeek, _). 

leapYear(Year) :- 
        Year =:= Year // 4 * 4, 
        ( 0 =:= Year // 100 -> 0 =\= Year // 400 ; true ). 