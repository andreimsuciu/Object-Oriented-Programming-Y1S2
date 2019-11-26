#include "Exceptions.h"

ValidException::ValidException(std::string _msg) : std::runtime_error{ _msg } {}

RepoException::RepoException(std::string _msg) : std::runtime_error{ _msg } {}

CtrlException::CtrlException(std::string _msg) : std::runtime_error{ _msg } {}

std::string ValidException::msg() const noexcept
{
	std::string res{ "Validator Exception: " };

	res += std::runtime_error::what();
	return res;
}

std::string RepoException::msg() const noexcept
{
	std::string res{ "Repo Exception: " };

	res += std::runtime_error::what();
	return res;
}

std::string CtrlException::msg() const noexcept
{
	std::string res{ "Controller Exception: " };

	res += std::runtime_error::what();
	return res;
}