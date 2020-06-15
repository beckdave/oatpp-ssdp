/***************************************************************************
 *
 * Project         _____    __   ____   _      _
 *                (  _  )  /__\ (_  _)_| |_  _| |_
 *                 )(_)(  /(__)\  )( (_   _)(_   _)
 *                (_____)(__)(__)(__)  |_|    |_|
 *
 *
 * Copyright 2018-present, Leonid Stryzhevskyi <lganzzzo@gmail.com>
 *                         Benedikt-Alexander Mokroß <oatpp@bamkrs.de>
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 ***************************************************************************/

#include "SsdpMessage.hpp"

namespace oatpp { namespace ssdp {

data::stream::DefaultInitializedContext SsdpMessage::DEFAULT_CONTEXT(data::stream::StreamType::STREAM_FINITE);

SsdpMessage::SsdpMessage(const std::shared_ptr<base::StrBuffer>& incomingData)
  : m_mode(data::stream::IOMode::BLOCKING)
  , m_inBuffer(incomingData)
  , m_in(incomingData, incomingData->getData(), incomingData->getSize())
{}

v_io_size SsdpMessage::flushToStream(OutputStream* stream) {
  return stream->writeExactSizeDataSimple(m_out.getData(), m_out.getCurrentPosition());
}

v_io_size SsdpMessage::write(const void *buff, v_buff_size count, async::Action& action) {
  if (m_out.getCurrentPosition() + count > MAX_MESSAGE_SIZE) {
    count = MAX_MESSAGE_SIZE - m_out.getCurrentPosition();
  }
  return m_out.write(buff, count, action);
}

v_io_size SsdpMessage::read(void *buff, v_buff_size count, async::Action& action) {
  return m_in.read(buff, count, action);
}

void SsdpMessage::setOutputStreamIOMode(data::stream::IOMode ioMode) {
  m_mode = ioMode;
}

data::stream::IOMode SsdpMessage::getOutputStreamIOMode() {
  return m_mode;
}

data::stream::Context& SsdpMessage::getOutputStreamContext() {
  return DEFAULT_CONTEXT;
}

void SsdpMessage::setInputStreamIOMode(data::stream::IOMode ioMode) {
  m_mode = ioMode;
}

data::stream::IOMode SsdpMessage::getInputStreamIOMode() {
  return m_mode;
}

data::stream::Context& SsdpMessage::getInputStreamContext() {
  return DEFAULT_CONTEXT;
}

}}
