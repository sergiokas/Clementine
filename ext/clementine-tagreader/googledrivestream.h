/* This file is part of Clementine.
   Copyright 2012, David Sansome <me@davidsansome.com>
   
   Clementine is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   
   Clementine is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with Clementine.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef GOOGLEDRIVESTREAM_H
#define GOOGLEDRIVESTREAM_H

#include <QUrl>

#include <google/sparsetable>
#include <taglib/tiostream.h>

class QNetworkAccessManager;

class GoogleDriveStream : public TagLib::IOStream {
 public:
  GoogleDriveStream(const QUrl& url,
                    const QString& filename,
                    const long length,
                    const QString& auth,
                    QNetworkAccessManager* network);

  // Taglib::IOStream
  virtual TagLib::FileName name() const;
  virtual TagLib::ByteVector readBlock(ulong length);
  virtual void writeBlock(const TagLib::ByteVector&);
  virtual void insert(const TagLib::ByteVector&, ulong, ulong);
  virtual void removeBlock(ulong, ulong);
  virtual bool readOnly() const;
  virtual bool isOpen() const;
  virtual void seek(long offset, TagLib::IOStream::Position p);
  virtual void clear();
  virtual long tell() const;
  virtual long length();
  virtual void truncate(long);

 private:
  bool CheckCache(int start, int end);
  void FillCache(int start, TagLib::ByteVector data);
  TagLib::ByteVector GetCached(int start, int end);

 private:
  const QUrl url_;
  const QString filename_;
  const QByteArray encoded_filename_;
  const ulong length_;
  const QString auth_;

  int cursor_;
  QNetworkAccessManager* network_;

  google::sparsetable<char> cache_;
};

#endif // GOOGLEDRIVESTREAM_H