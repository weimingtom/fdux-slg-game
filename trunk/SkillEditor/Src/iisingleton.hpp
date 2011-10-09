#pragma warning(disable:4819)
#ifndef IISINGLETON_HPP
#define IISINGLETON_HPP
#include "iiexception.hpp"

namespace izayoi
{

/**
 * @brief 单例模板
 */
template<class T>
class IISingleton
{
    protected:
        ///实例指针
        static T* __instance;

        /**
         * @brief 构造
         * @throw IIException 如果类已经被构造
         */
        IISingleton()
        {
            if(__instance != 0)
            {
                throw(IIException("IISingleton error : constructor"));
            }
            __instance = static_cast<T*>(this);
        }

        /**
         * @brief 析构实例
         * @throw IIException 如果例程已经被析构
         */
        ~IISingleton()
        {
            if(__instance == 0)
            {
                throw(IIException("IISingleton error : destructors"));
            }
            __instance = 0;
        }
    public:
        /**
         * @brief 得到实例引用
         * @return T& 实例引用
         * @throw IIException 如果类没有被构造，且不能无参数构造
         */
        static T& getSingleton(void)
        {
            if(__instance == 0 && T::constructor() == false)
            {
                throw(IIException("IISingleton error : getSingleton"));
            }
            return *__instance;
        }

        /**
         * @brief 得到实例指针
         * @return T* 实例指针
         * @throw IIException 如果类没有被构造，且不能无参数构造
         */
        static T* getSingletonPtr()
        {
            if(__instance == 0 && T::constructor() == false)
            {
                throw(IIException("IISingleton error : getSingletonPtr"));
            }
            return __instance;
        }

        /**
         * @brief 无参数构造
         *
         * 可以集成覆盖这个静态方法实现无参数构造，默认不允许无参数构造
         * @return 是否允许无参数构造
         */
        static bool constructor()
        {
            return false;
        }
};

template<class T>
T* IISingleton<T>::__instance = 0;

}



#endif
