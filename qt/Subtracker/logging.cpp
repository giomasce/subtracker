
#include "logging.h"

#include <boost/shared_ptr.hpp>
#include <boost/date_time/posix_time/posix_time_types.hpp>
#include <boost/log/core.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/sources/logger.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <boost/log/utility/setup/console.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/support/date_time.hpp>
#include <boost/log/sinks/sync_frontend.hpp>
#include <boost/log/sinks/text_file_backend.hpp>
#include <boost/log/sinks/text_ostream_backend.hpp>

auto consoleSink = boost::log::add_console_log(std::clog);

void setup_logging(boost::log::v2_mt_posix::trivial::severity_level min_severity) {
  boost::log::add_common_attributes();
     boost::log::core::get()->add_global_attribute("Scope",
          boost::log::attributes::named_scope());
      boost::log::core::get()->set_filter(
          boost::log::trivial::severity >= min_severity
      );

      /* log formatter:
       * [TimeStamp] [ThreadId] [Severity Level] [Scope] Log message
       */
      auto fmtTimeStamp = boost::log::expressions::
          format_date_time<boost::posix_time::ptime>("TimeStamp", "%Y-%m-%d %H:%M:%S.%f");
      auto fmtThreadId = boost::log::expressions::
          attr<boost::log::attributes::current_thread_id::value_type>("ThreadID");
      auto fmtSeverity = boost::log::expressions::
          attr<boost::log::trivial::severity_level>("Severity");
      auto fmtScope = boost::log::expressions::format_named_scope("Scope",
          boost::log::keywords::format = "%n,%f:%l",
          boost::log::keywords::iteration = boost::log::expressions::reverse,
          boost::log::keywords::depth = 2);
      boost::log::formatter logFmt =
          boost::log::expressions::format("[%1%] (%2%) [%3%] [%4%] %5%")
          % fmtTimeStamp % fmtThreadId % fmtSeverity % fmtScope
          % boost::log::expressions::smessage;

      /* console sink */
      consoleSink->set_formatter(logFmt);
}

void flush_log() {
    consoleSink->flush();
}

//BOOST_LOG_FUNCTION();
