#pragma once
#include "Booking.h"

Status compareBookingNum(PBOOKING booking1, PBOOKING booking2);
Status insertBookListTail(PBOOKING& book_list, PBOOKING& booking);
Status insertBookList(PBOOKING& book_list);

char* getBookingNum(PBOOKING book_list, const char* date, const char* train_name);
