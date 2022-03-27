#include "Logger.h"
#include <library/Mutex.h>

#include <iostream>
#include <ctime>

#include<QDebug>

#if defined(Q_OS_WIN)
#include <Windows.h>
#endif

namespace Logger
{
	CMutex g_oMutex;

	std::string DateTime()
	{
		time_t nNow = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
		char buf[80];
		tm grT;
		localtime_s(&grT, &nNow);
		strftime(buf, sizeof(buf), "%A %d %R", &grT);
		return buf;
	}

#if defined(Q_OS_WIN)
	HANDLE g_pHandle = nullptr;
	enum EColor : uint8_t
	{
		Black,
		DarkBlue,
		DarkGreen,
		DarkTurkeyse,
		DarkRed,
		DarkPurple,
		DarkYellow,
		DarkWhite,
		Gray,
		BrightBlue,
		BrightGreen,
		BrightTurkeyse,
		BrightRed,
		BrightPurple,
		BrightYellow,
		BrightWhite
	};

	void SetColor(const EColor i_eColor)
	{
		if (!g_pHandle) {
			g_pHandle = GetStdHandle(STD_OUTPUT_HANDLE);
		}

		SetConsoleTextAttribute(g_pHandle, i_eColor);
	}

	void Output(const std::string& i_sWhat, const Logger::EColor i_eColor)
	{
		Logger::g_oMutex.lock();
		Logger::SetColor(i_eColor);
		std::cout << i_sWhat << std::endl;
		Logger::SetColor(Logger::BrightWhite);
		Logger::g_oMutex.unlock();
	}
#endif

}


// Set Title=====================================================
void Logger::SetTitle(const std::string& i_sTitle){
#if defined(Q_OS_WIN)
	SetConsoleTitleA(i_sTitle.c_str());
#else
	std::cout << "\033]0;" << i_sTitle << "\007";
#endif
}

// Log=====================================================
void Logger::Log(const std::string& i_sMsg, ESeverity i_eSeverity)
{
	// Set string time
	std::string stOut("[" + DateTime() + "] ");

#if defined(Q_OS_WIN)
	EColor eColor = BrightWhite;

	switch (i_eSeverity)
	{
	case ESeverity::Fatal:
		stOut += "[Fatal]: ";
		eColor = DarkRed;
		break;
	case ESeverity::Error:
		stOut += "[Error]: ";
		eColor = BrightRed;
		break;
	case ESeverity::Warning:
		stOut += "[Warning]: ";
		eColor = BrightYellow;
		break;
	case ESeverity::Info:
		stOut += "[Info]: ";
		eColor = BrightTurkeyse;
		break;
	case ESeverity::Debug:
		stOut += "[Debug]: ";
		eColor = DarkTurkeyse;
		break;
	case ESeverity::Verbose:
		stOut += "[Verbose]: ";
		eColor = BrightGreen;
		break;
}
	stOut += i_sMsg;

	Output(stOut, eColor);

#else
	Logger::g_oMutex.lock();
	switch (i_eSeverity)
	{
	case ESeverity::Fatal:
		qCritical() << stOut.c_str() << "[Fatal]: " << i_sMsg.c_str();
		break;
	case ESeverity::Error:
		qCritical() << stOut.c_str() << "[Error]: " << i_sMsg.c_str();
		break;
	case ESeverity::Warning:
		qWarning() << stOut.c_str() << "[Warning]: " << i_sMsg.c_str();
		break;
	case ESeverity::Info:
		qInfo() << stOut.c_str() << "[Info]: " << i_sMsg.c_str();
		break;
	case ESeverity::Debug:
		qDebug() << stOut.c_str() << "[Debug]: " << i_sMsg.c_str();
		break;
	case ESeverity::Verbose:
		qDebug() << stOut.c_str() << "[Verbose]: " << i_sMsg.c_str();
		break;
	}
	Logger::g_oMutex.unlock();
#endif
}

// New Line=====================================================
void Logger::NewLine()
{
	Logger::g_oMutex.lock();
	qInfo("");
	Logger::g_oMutex.unlock();
}

// Cin Get===================================================
void Logger::WaitEnter()
{
	std::cin.get();
}