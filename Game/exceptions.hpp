#ifndef __EXCEPTIONS_HPP
#define __EXCEPTIONS_HPP

#include <string>
#include <exception>

class unknownColor : public std::exception {
	private:
		std::string s;
	public:
		unknownColor( const std::string & name ):
			s{ std::string{ "Unknown color '" } + name + "'!\n" }
		{}

		const char * what() const noexcept {
			return s.c_str();
		}
};

class fileNotFound : public std::exception {
	private:
		std::string s;
	public:
		fileNotFound( const std::string & name ):
			s{ std::string{ "File '" } + name + "'' not found!\n" }
		{}

		const char * what() const noexcept {
			return s.c_str();
		}
};

class unknownShape : public std::exception {
	private:
		std::string s;
	public:
		unknownShape( const std::string & name ):
			s{ std::string{ "Unknown shape '" } + name + "'!\n" }
		{}

		const char * what() const noexcept {
			return s.c_str();
		}
};

class invalidPosition : public std::exception {
	private:
		std::string s;
	public:
		invalidPosition( const char & readCharacter ):
			s{ std::string{ "Invalid position '" } + readCharacter + "'!\n" }
		{}

		const char * what() const noexcept {
			return s.c_str();
		}
};

class noSuchPicture : public std::exception {
	private:
		std::string s;
	public:
		noSuchPicture( const std::string & fileName ):
			s{ std::string{ "No file named '" } + fileName + "'' found!\n" }
		{}

		const char * what() const noexcept {
			return s.c_str();
		}
};

class storageSizeReached : public std::exception {
	private:
		std::string s;
	public:
		storageSizeReached( const int maxStorageSize ):
			s{ "Max amount of objects in storage (" + std::to_string(maxStorageSize) + ") reached!\n" }
		{}

		const char * what() const noexcept {
			return s.c_str();
		}
};

class endOfFile : public std::exception {};

#endif //__EXCEPTIONS_HPP
