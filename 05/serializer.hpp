Serializer::Serializer(std::ostream &out) : out_(out) {}

template <class T> Error Serializer::save(T &object) {
  return object.serialize(*this);
}

template <class... Args> Error Serializer::operator()(Args &&... args) {
  return process(std::forward<Args>(args)...);
}

Error Serializer::save(const bool val) {
  if (val) {
    out_ << "true" << Separator;
  } else {
    out_ << "false" << Separator;
  }

  return Error::NoError;
}

Error Serializer::save(const uint64_t val) {
  out_ << val << Separator;
  return Error::NoError;
}

template <class T> Error Serializer::process(T &&val) {
  return save(std::forward<T>(val));
}

template <class T, class... Args>
Error Serializer::process(T &&val, Args &&... args) {
  Error error = save(std::forward<T>(val));

  if (error == Error::NoError) {
    return process(std::forward<Args>(args)...);
  } else {
    return error;
  }
}

Deserializer::Deserializer(std::istream &in) : in_(in) {}

template <class T> Error Deserializer::load(T &object) {
  return object.serialize(*this);
}

template <class... ArgsT> Error Deserializer::operator()(ArgsT &&... args) {
  return process(std::forward<ArgsT>(args)...);
}

Error Deserializer::load(bool &val) {
  std::string text;
  in_ >> text;

  if (text == "true") {
    val = true;
  } else if (text == "false") {
    val = false;
  } else {
    return Error::CorruptedArchive;
  }

  return Error::NoError;
}

Error Deserializer::load(uint64_t &val) {
  std::string text;
  in_ >> text;
  uint64_t res = 0;

  if (text.size() == 0) {
    return Error::CorruptedArchive;
  }

  for (size_t i = 0; i < text.size(); i++) {
    if (isdigit(text[i])) {
      res = res * 10 + (text[i] - '0');
    } else {
      return Error::CorruptedArchive;
    }
  }

  val = res;
  return Error::NoError;
}

template <class T> Error Deserializer::process(T &&val) {
  return load(std::forward<T>(val));
}

template <class T, class... Args>
Error Deserializer::process(T &&val, Args &&... args) {
  Error error = load(std::forward<T>(val));
  if (error == Error::NoError) {
    return process(std::forward<Args>(args)...);
  } else {
    return error;
  }
}
