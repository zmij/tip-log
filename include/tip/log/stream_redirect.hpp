/*
 * stream_redirect.hpp
 *
 *  Created on: Jan 15, 2016
 *      Author: zmij
 */

#ifndef TIP_LOG_STREAM_REDIRECT_HPP_
#define TIP_LOG_STREAM_REDIRECT_HPP_

#include <iostream>
#include <fstream>
#include <string>

namespace tip {
namespace log {

class stream_redirect {
public:
    stream_redirect(::std::ostream& stream,
            ::std::string const& file_name,
            ::std::ios_base::openmode open_mode
                 = ::std::ios_base::out | ::std::ios_base::app) :
        stream_(stream), old_(stream.rdbuf())
    {
        file_.open(file_name.c_str(), open_mode);
        if (!file_.good()) {
            std::ostringstream msg;
            msg << "Failed to open file " << file_name
                    << ": " << strerror(errno) << "\n";
            throw std::runtime_error(msg.str());
        }
        stream_.rdbuf(file_.rdbuf());
    }
    ~stream_redirect()
    {
        stream_.flush();
        stream_.rdbuf(old_);
    }
private:
    std::ostream& stream_;
    std::streambuf* old_;
    std::ofstream file_;
};

}  // namespace log
}  // namespace tip


#endif /* TIP_LOG_STREAM_REDIRECT_HPP_ */
