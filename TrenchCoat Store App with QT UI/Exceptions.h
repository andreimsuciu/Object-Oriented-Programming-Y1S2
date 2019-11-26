#pragma once

#include <exception>
#include <stdexcept>
#include <string>

class ValidException : public std::runtime_error
{
public:
	ValidException(std::string _msg);
	std::string msg() const noexcept;
};

class RepoException : public std::runtime_error
{
public:
	RepoException(std::string _msg);
	std::string msg() const noexcept;
};

class CtrlException : public std::runtime_error
{
public:
	CtrlException(std::string _msg);
	std::string msg() const noexcept;
};