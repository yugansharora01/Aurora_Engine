#include "pch.h"
#include "AuroraException.h"

AuroraException::AuroraException(int line, const char *file) noexcept
    : line(line), file(file)
{
}

const char *AuroraException::what() const noexcept
{
    std::ostringstream oss;
    oss << GetType() << std::endl
        << GetOriginString();
    whatBuffer = oss.str();
    return whatBuffer.c_str();
}

const char *AuroraException::GetType() const noexcept
{
    return "Aurora Exception";
}

int AuroraException::GetLine() const noexcept
{
    return line;
}

const std::string &AuroraException::GetFile() const noexcept
{
    return file;
}

std::string AuroraException::GetOriginString() const noexcept
{
    std::ostringstream oss;
    oss << "[FILE]" << file << std::endl
        << "[LINE]" << line;
    return oss.str();
}
