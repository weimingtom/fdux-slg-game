#ifndef IIEXCEPTION_HPP
#define IIEXCEPTION_HPP
#include <string>

namespace izayoi
{

/**
 * @brief 违例消息
 */
class IIException
{
    protected:
        std::string message;
    public:

        /**
         * @brief 创建违例
         * @param msg 违例消息
         */
        IIException(const std::string msg);

        /**
         * @brief 得到违例消息
         * @return 违例消息
         */
        const std::string& getMessage();
};

}

#endif
