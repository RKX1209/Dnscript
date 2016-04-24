#ifndef __REGISTER_HPP__
#define __REGISTER_HPP__

class Register {
public:
  std::string id;
  Register() : id("") {}
  Register(std::string _id) : id(_id) {}
  std::string getId() { return id; }
};

class Label {
public:
  std::string id;
  Label() : id("") {}
  Label(std::string _id) : id(_id) {}
  std::string getId() { return id; }
};

#endif
