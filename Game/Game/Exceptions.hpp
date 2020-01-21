#ifndef __EXCEPTIONS_HPP
#define __EXCEPTIONS_HPP

#include <string>
#include <exception>

class unknownColor : public std::exception {
	private:
		std::string error;
	public:
		unknownColor( const std::string & name ){
			error = "(!)-- Unknown color " + name + ".\n";
		}

		const char * what() const noexcept {
			return error.c_str();
		}
};

class fileNotFound : public std::exception {
	private:
		std::string error;
	public:
		fileNotFound( const std::string & name ){
			error = "(!)--File " + name + " not found.\n";
		}

		const char * what() const noexcept {
			return error.c_str();
		}
};

class unknownShape : public std::exception {
	private:
		std::string error;
	public:
		unknownShape( const std::string & name ){
			error = "(!)-- Unknown shape "  + name + ".\n";
		}

		const char * what() const noexcept {
			return error.c_str();
		}
};

class invalidPosition : public std::exception {
	private:
		std::string error;
	public:
		invalidPosition( const char & readCharacter ){
			error = "(!)-- Invalid position " + std::to_string(readCharacter) + ".\n";
		}

		const char * what() const noexcept {
			return error.c_str();
		}
};

class noSuchPicture : public std::exception {
	private:
		std::string error;
	public:
		noSuchPicture( const std::string & fileName ){
			error = "(!)-- No file named " + fileName + "found.\n";
		}
		
		const char * what() const noexcept {
			return error.c_str();
		}
};

class storageSizeReached : public std::exception {
	private:
		std::string error;
	public:
		storageSizeReached( const int maxStorageSize ){
			error = "(!)-- Max amount of objects in storage (" + std::to_string(maxStorageSize) + ") reached!\n";
		}

		const char * what() const noexcept {
			return error.c_str();
		}
};

class sortingFailed : public std::exception {
	private:
		std::string error;
	public:
		sortingFailed(const std::string & file, const int line){
			error = "(!)-- Failed to sort container in file " + file + " at line " + std::to_string(line) + ".\n";
		}

		const char* what() const noexcept {
			return error.c_str();
		}
};

class endOfFile : public std::exception {};

class divideByZero : public std::exception {
	private:
		std::string error;
	public:
		divideByZero(const std::string & file, const int line){
			error = "(!)-- Division by zero in file " + file + " at line " + std::to_string(line) + ".\n";
		}

		const char* what() const noexcept{
			return error.c_str();
		}
};

#endif //__EXCEPTIONS_HPP
