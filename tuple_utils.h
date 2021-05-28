#ifndef TUPLE_UTILS_H
#define TUPLE_UTILS_H

/**
*   https://habr.com/ru/post/318236/
*/

#include <tuple>

namespace tuple_utils
{
    template<class TCallback, class ...TParams>
    void tupleForeach(TCallback& callback, const std::tuple<TParams...>& tuple);

    namespace
    {

        template<std::size_t Index, class TCallback, class ...TParams>
        struct _foreach_
        {
            static void tupleForeach_(TCallback& callback, const std::tuple<TParams...>& tuple)
            {
                // такой пересчёт необходим для выполнения callback'a над элементами в порядке их следования
                const std::size_t idx = sizeof...(TParams) - Index;
                callback.operator()(std::get<idx>(tuple), idx);
                _foreach_<Index - 1, TCallback, TParams...>::tupleForeach_(callback, tuple);
            }
        };

        template<class TCallback, class ...TParams>
        struct _foreach_<0, TCallback, TParams...>
        {
            static void tupleForeach_(TCallback& /*callback*/, const std::tuple<TParams...>& /*tuple*/) {}
        };

    } //
    template<class TCallback, class ...TParams>
    void tupleForeach(TCallback& callback, const std::tuple<TParams...>& tuple)
    {
        _foreach_<sizeof...(TParams), TCallback, TParams...>::tupleForeach_(callback, tuple);
    }

} // tuple_utils


#endif