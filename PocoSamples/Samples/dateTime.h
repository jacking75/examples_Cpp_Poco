#pragma once

#include <Poco/DateTime.h>
#include <Poco/Timezone.h>
#include <Poco/Format.h>
#include <Poco/DateTimeFormatter.h>

#include <string>


void displayDateTime(const Poco::DateTime& dateTime)
{
	std::cout << Poco::format("            year = %d", dateTime.year()) << std::endl;
	std::cout << Poco::format("           month = %d\t(1 to 12)", dateTime.month()) << std::endl;
	std::cout << Poco::format("             day = %d\t(1 to 31)", dateTime.day()) << std::endl;
	std::cout << Poco::format("            hour = %d\t(0 to 23)", dateTime.hour()) << std::endl;
	std::cout << Poco::format("          minute = %d\t(0 to 59)", dateTime.minute()) << std::endl;
	std::cout << Poco::format("          second = %d\t(0 to 59)", dateTime.second()) << std::endl;
	std::cout << Poco::format("     millisecond = %d\t(0 to 999)", dateTime.millisecond()) << std::endl;
	std::cout << Poco::format("     microsecond = %d\t(0 to 999)", dateTime.microsecond()) << std::endl;
	std::cout << Poco::format("            isAM = %s\t(true or false)", std::string(dateTime.isAM() ? "true" : "false")) << std::endl;
	std::cout << Poco::format("            isPM = %s\t(true or false)", std::string(dateTime.isPM() ? "true" : "false")) << std::endl;
	std::cout << Poco::format("      isLeapYear = %s\t(true or false)", std::string(Poco::DateTime::isLeapYear(dateTime.year()) ? "true" : "false")) << std::endl;
	std::cout << Poco::format("        hourAMPM = %d\t(0 to 12)", dateTime.hourAMPM()) << std::endl;
	std::cout << Poco::format("       dayOfWeek = %d\t(0 to 6,   0: Sunday)", dateTime.dayOfWeek()) << std::endl;
	std::cout << Poco::format("       dayOfYear = %d\t(1 to 366, 1: January 1)", dateTime.dayOfYear()) << std::endl;
	std::cout << Poco::format("     daysOfMonth = %d\t(1 to 366, 1: January 1)", Poco::DateTime::daysOfMonth(dateTime.year(), dateTime.month())) << std::endl;
	std::cout << Poco::format("            week = %d\t(0 to 53,  1: the week containing January 4)", dateTime.week()) << std::endl;
}

void IntUnixTime()
{
	Poco::DateTime dateTime;
	auto now = dateTime.timestamp();
	
	std::cout << "epochMicroseconds" << now.epochMicroseconds() << std::endl;
	std::cout << "epochMicroseconds" << now.epochTime() << std::endl;
}

void Sample_DateTime()
{
	Poco::DateTime dateTime;

	std::cout << "  Current DateTime (UTC)" << std::endl;
	displayDateTime(dateTime);


	std::cout << Poco::format("  Current DateTime (Locat Time: %s [GMT%+d])", Poco::Timezone::name(), Poco::Timezone::tzd() / (60 * 60)) << std::endl;
	dateTime.makeLocal(Poco::Timezone::tzd());
	displayDateTime(dateTime);

	std::cout << Poco::format(Poco::DateTimeFormatter::format(dateTime, "  DateTimeFormatter: %w %b %e %H:%M:%S %%s %Y"), Poco::Timezone::name()) << std::endl;

	
	IntUnixTime();
}