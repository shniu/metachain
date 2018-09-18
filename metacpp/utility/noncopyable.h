//
// Created by shniu on 18-9-18.
//

#ifndef METACHAIN_NONCOPYABLE_H
#define METACHAIN_NONCOPYABLE_H

namespace metachain {

    /// forbidden copying
    class noncopyable {
    public:
        /// disallow copying
        noncopyable(const noncopyable&) = delete;
        noncopyable& operator=(const noncopyable&) = delete;

    protected:
        noncopyable(){}
    };
}

#endif //METACHAIN_NONCOPYABLE_H
