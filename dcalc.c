#include <stdio.h>
#include <time.h>
#include <assert.h>

int domToday();
int monthToday();
int yeartoday();

int monthDays(int year, int month);

void printDate(int year, int month, int dom);


struct tm *now;
time_t timer;

int main(int argc, char **argv) {

	int delta=0;

	if (argc!=2) {
		printf("Expect a single argument... number of days from today.\n");
		printf("Assuming today's date (delta=0)\n");
	} else delta=atoi(argv[1]);

	int year=yearToday();
	int month=monthToday();
	int dom=domToday();

/* Accounting for the Leap Years; If the months are 4,6,9,&11 monthdays will be 30, other wise they get tested for being a leap year or just a month with 31 days */

int monthDays(int year, int month){
	if (month == 4 || month == 6 || month == 9 || month == 11){
		return 30;
	}
	else if(month == 2){
		if(((year%4 == 0) && (year%100 != 0)) || (year%400 == 0)){
			return 29;
		}
		else{
			return 28;
		}
	}
	else{
		return 31;
	}
}

/* if the number entered is greater than 0, it will add to the current year and add to the current month */

	if(delta > 0){
		while(delta > 0){
			if(dom != monthDays(year,month)){
				dom++;
			}
			else if (dom == monthDays(year,month) && month == 12){
				dom = 1;
				month= 1;
				year++;
			}
			else if (dom == monthDays(year,month)){
				dom = 1;
				month++;
			}
			delta--;
		}
	}

/* if the number entered is less than 0, it will subtract from the year and subtract from the month */

	if(delta < 0){
		while(delta < 0){
			if(dom != 1){
				dom--;
			}
			else if (dom == 1 && month == 1){
				month = 12;
				dom = monthDays(year,month);
				year--;
			}
			else if (dom == 1){
				dom = monthDays(year,month);
				month--;
			}
			delta++;
		}
	}


	printDate(year,month,dom);
}

int domToday() {
	timer=time(NULL);
	now = localtime(&timer);
	return now->tm_mday;
}

int monthToday() {
	timer=time(NULL);
	now = localtime(&timer);
	return now->tm_mon+1;
}

int yearToday() {
	timer=time(NULL);
	now = localtime(&timer);
	return now->tm_year+1900;
}

void printDate(int year, int month, int dom) {
	assert(year>=0);
	assert(month>0);
	assert(month<=12);
	assert(dom>0);
	assert(dom<=31);
	char* monthNames[12]={"January","February","March","April","May",
			"June","July","August","September","October","November","December"};
	printf("New date is: %s %2d, %d\n",monthNames[month-1],dom,year);
}


