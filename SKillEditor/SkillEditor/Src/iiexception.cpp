#include "iiexception.hpp"

using namespace std;
using namespace izayoi;

IIException::IIException(const string msg)
{
    message = msg;
}

const string& IIException::getMessage()
{
    return message;
}
