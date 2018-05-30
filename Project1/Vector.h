#pragma once
#include <cstddef>
#include <cstring>
#include <utility>
#include <iterator>
#include <stdexcept>

	template <typename T>
	class vector {
	public:
		// types:
		typedef T                                     value_type;
		typedef T &                                   reference;
		typedef const T &                             const_reference;
		typedef T *                                   pointer;
		typedef const T *                             const_pointer;
		typedef T *                                   iterator;
		typedef const T *                             const_iterator;
		typedef std::reverse_iterator<iterator>       reverse_iterator;
		typedef std::reverse_iterator<const_iterator> const_reverse_iterator;
		typedef ptrdiff_t                             difference_type;
		typedef unsigned int                          size_type;

		// 23.3.11.2, construct/copy/destroy:
		vector() noexcept;
		explicit vector(size_type n);
		vector(size_type n, const T &val);
		vector(typename vector<T>::iterator first, typename vector<T>::iterator last);
		vector(std::initializer_list<T>);
		vector(const vector<T> &);
		vector(vector<T> &&) noexcept;
		~vector();
		vector<T> & operator = (const vector<T> &);
		vector<T> & operator = (vector<T> &&);
		vector<T> & operator = (std::initializer_list<T>);
		void assign(size_type, const T &value);
		void assign(typename vector<T>::iterator, typename vector<T>::iterator);
		void assign(std::initializer_list<T>);

		// iterators:
		iterator begin() noexcept;
		const_iterator cbegin() const noexcept;
		iterator end() noexcept;
		const_iterator cend() const noexcept;
		reverse_iterator rbegin() noexcept;
		const_reverse_iterator crbegin() const noexcept;
		reverse_iterator rend() noexcept;
		const_reverse_iterator crend() const noexcept;

		// 23.3.11.3, capacity:
		bool empty() const noexcept;
		size_type size() const noexcept;
		size_type max_size() const noexcept;
		size_type capacity() const noexcept;
		void resize(size_type);
		void resize(size_type, const T &);
		void reserve(size_type);
		void shrink_to_fit();

		// element access
		reference operator [](size_type);
		const_reference operator [](size_type) const;
		reference at(size_type);
		const_reference at(size_type) const;
		reference front();
		const_reference front() const;
		reference back();
		const_reference back() const;

		// 23.3.11.4, data access:
		T * data() noexcept;
		const T * data() const noexcept;

		// 23.3.11.5, modifiers:
		template <class ... Args> void emplace_back(Args && ... args);
		void push_back(const T &);
		void push_back(T &&);
		void pop_back();

		template <class ... Args> iterator emplace(const_iterator, Args && ...);
		iterator insert(const_iterator, const T &);
		iterator insert(const_iterator, T &&);
		iterator insert(const_iterator, size_type, const T&);
		template <class InputIt> iterator insert(const_iterator, InputIt, InputIt);
		iterator insert(const_iterator, std::initializer_list<T>);
		iterator erase(const_iterator);
		iterator erase(const_iterator, const_iterator);
		void swap(vector<T> &);
		void clear() noexcept;

		bool operator == (const vector<T> &) const;
		bool operator != (const vector<T> &) const;
		bool operator < (const vector<T> &) const;
		bool operator <= (const vector<T> &) const;
		bool operator > (const vector<T> &) const;
		bool operator >= (const vector<T> &) const;
	private:
		size_type reserved_size = 4;
		size_type vector_size = 0;
		T *arr;

		inline void reallocate();

	};



	template <typename T>
	vector<T>::vector() noexcept {
		arr = new T[reserved_size];
	}

	template <typename T>
	vector<T>::vector(typename vector<T>::size_type n) {
		size_type i;
		reserved_size = n << 2;
		arr = new T[reserved_size];
		for (i = 0; i < n; ++i)
			arr[i] = T();
		vector_size = n;
	}

	template <typename T>
	vector<T>::vector(typename vector<T>::size_type n, const T &value) {
		size_type i;
		reserved_size = n << 2;
		arr = new T[reserved_size];
		for (i = 0; i < n; ++i)
			arr[i] = value;
		vector_size = n;
	}

	template <typename T>
	vector<T>::vector(typename vector<T>::iterator first, typename vector<T>::iterator last) {
		size_type i, count = last - first;
		reserved_size = count << 2;
		arr = new T[reserved_size];
		for (i = 0; i < count; ++i, ++first)
			arr[i] = *first;
		vector_size = count;
	}

	template <typename T>
	vector<T>::vector(std::initializer_list<T> lst) {
		reserved_size = lst.size() << 2;
		arr = new T[reserved_size];
		for (auto &item : lst)
			arr[vector_size++] = item;
	}

	template <typename T>
	vector<T>::vector(const vector<T> &other) {
		size_type i;
		reserved_size = other.reserved_size;
		arr = new T[reserved_size];
		for (i = 0; i < other.vector_size; ++i)
			arr[i] = other.arr[i];
		vector_size = other.vector_size;
	}

	template <typename T>
	vector<T>::vector(vector<T> &&other) noexcept {
		size_type i;
		reserved_size = other.reserved_size;
		arr = new T[reserved_size];
		for (i = 0; i < other.vector_size; ++i)
			arr[i] = std::move(other.arr[i]);
		vector_size = other.vector_size;
	}

	template <typename T>
	vector<T>::~vector() {
		delete[] arr;
	}

	template <typename T>
	vector<T> & vector<T>::operator = (const vector<T> &other) {
		size_type i;
		if (reserved_size < other.vector_size) {
			reserved_size = other.vector_size << 2;
			reallocate();
		}
		for (i = 0; i < other.vector_size; ++i)
			arr[i] = other.arr[i];
		vector_size = other.vector_size;
	}

	template <typename T>
	vector<T> & vector<T>::operator = (vector<T> &&other) {
		size_type i;
		if (reserved_size < other.vector_size) {
			reserved_size = other.vector_size << 2;
			reallocate();
		}
		for (i = 0; i < other.vector_size; ++i)
			arr[i] = std::move(other.arr[i]);
		vector_size = other.vector_size;
	}

	template <typename T>
	vector<T> & vector<T>::operator = (std::initializer_list<T> lst) {
		if (reserved_size < lst.size()) {
			reserved_size = lst.size() << 2;
			reallocate();
		}
		vector_size = 0;
		for (auto &item : lst)
			arr[vector_size++] = item;
	}

	template <typename T>
	void vector<T>::assign(typename vector<T>::size_type count, const T &value) {
		size_type i;
		if (count > reserved_size) {
			reserved_size = count << 2;
			reallocate();
		}
		for (i = 0; i < count; ++i)
			arr[i] = value;
		vector_size = count;
	}

	template <typename T>
	void vector<T>::assign(typename vector<T>::iterator first, typename vector<T>::iterator last) {
		size_type i, count = last - first;
		if (count > reserved_size) {
			reserved_size = count << 2;
			reallocate();
		}
		for (i = 0; i < count; ++i, ++first)
			arr[i] = *first;
		vector_size = count;
	}

	template <typename T>
	void vector<T>::assign(std::initializer_list<T> lst) {
		size_type i, count = lst.size();
		if (count > reserved_size) {
			reserved_size = count << 2;
			reallocate();
		}
		i = 0;
		for (auto &item : lst)
			arr[i++] = item;
	}


	template <typename T>
	typename vector<T>::iterator vector<T>::begin() noexcept {
		return arr;
	}

	template <typename T>
	typename vector<T>::const_iterator vector<T>::cbegin() const noexcept {
		return arr;
	}

	template <typename T>
	typename vector<T>::iterator vector<T>::end() noexcept {
		return arr + vector_size;
	}

	template <typename T>
	typename vector<T>::const_iterator vector<T>::cend() const noexcept {
		return arr + vector_size;
	}

	template <typename T>
	typename vector<T>::reverse_iterator vector<T>::rbegin() noexcept {
		return reverse_iterator(arr + vector_size);
	}

	template <typename T>
	typename vector<T>::const_reverse_iterator vector<T>::crbegin() const noexcept {
		return reverse_iterator(arr + vector_size);
	}

	template <typename T>
	typename vector<T>::reverse_iterator vector<T>::rend() noexcept {
		return reverse_iterator(arr);
	}

	template <typename T>
	typename vector<T>::const_reverse_iterator vector<T>::crend() const noexcept {
		return reverse_iterator(arr);
	}


	template <typename T>
	inline void vector<T>::reallocate() {
		T *tarr = new T[reserved_size];
		memcpy(tarr, arr, vector_size * sizeof(T));
		delete[] arr;
		arr = tarr;
	}


	template <typename T>
	bool vector<T>::empty() const noexcept {
		return vector_size == 0;
	}

	template <typename T>
	typename vector<T>::size_type vector<T>::size() const noexcept {
		return vector_size;
	}

	template <typename T>
	typename vector<T>::size_type vector<T>::max_size() const noexcept {
		return LNI_VECTOR_MAX_SZ;
	}

	template <typename T>
	typename vector<T>::size_type vector<T>::capacity() const noexcept {
		return reserved_size;
	}

	template <typename T>
	void vector<T>::resize(typename vector<T>::size_type sz) {
		if (sz > vector_size) {
			if (sz > reserved_size) {
				reserved_size = sz;
				reallocate();
			}
		}
		else {
			size_type i;
			for (i = vector_size; i < sz; ++i)
				arr[i].~T();
		}
		vector_size = sz;
	}

	template <typename T>
	void vector<T>::resize(typename vector<T>::size_type sz, const T &c) {
		if (sz > vector_size) {
			if (sz > reserved_size) {
				reserved_size = sz;
				reallocate();
			}
			size_type i;
			for (i = vector_size; i < sz; ++i)
				arr[i] = c;
		}
		else {
			size_type i;
			for (i = vector_size; i < sz; ++i)
				arr[i].~T();
		}
		vector_size = sz;
	}

	template <typename T>
	void vector<T>::reserve(typename vector<T>::size_type _sz) {
		if (_sz > reserved_size) {
			reserved_size = _sz;
			reallocate();
		}
	}

	template <typename T>
	void vector<T>::shrink_to_fit() {
		reserved_size = vector_size;
		reallocate();
	}


	template <typename T>
	typename vector<T>::reference vector<T>::operator [](typename vector<T>::size_type idx) {
		return arr[idx];
	}

	template <typename T>
	typename vector<T>::const_reference vector<T>::operator [](typename vector<T>::size_type idx) const {
		return arr[idx];
	}

	template <typename T>
	typename vector<T>::reference vector<T>::at(size_type pos) {
		if (pos < vector_size)
			return arr[pos];
		else
			throw std::out_of_range("accessed position is out of range");
	}

	template <typename T>
	typename vector<T>::const_reference vector<T>::at(size_type pos) const {
		if (pos < vector_size)
			return arr[pos];
		else
			throw std::out_of_range("accessed position is out of range");
	}

	template <typename T>
	typename vector<T>::reference vector<T>::front() {
		return arr[0];
	}

	template <typename T>
	typename vector<T>::const_reference vector<T>::front() const {
		return arr[0];
	}

	template <typename T>
	typename vector<T>::reference vector<T>::back() {
		return arr[vector_size - 1];
	}

	template <typename T>
	typename vector<T>::const_reference vector<T>::back() const {
		return arr[vector_size - 1];
	}


	template <typename T>
	T * vector<T>::data() noexcept {
		return arr;
	}

	template <typename T>
	const T * vector<T>::data() const noexcept {
		return arr;
	}


	template <typename T>
	template <class ... Args>
	void vector<T>::emplace_back(Args && ... args) {
		if (vector_size == reserved_size) {
			reserved_size <<= 2;
			reallocate();
		}
		arr[vector_size] = std::move(T(std::forward<Args>(args) ...));
		++vector_size;
	}

	template <typename T>
	void vector<T>::push_back(const T &val) {
		if (vector_size == reserved_size) {
			reserved_size <<= 2;
			reallocate();
		}
		arr[vector_size] = val;
		++vector_size;
	}

	template <typename T>
	void vector<T>::push_back(T &&val) {
		if (vector_size == reserved_size) {
			reserved_size <<= 2;
			reallocate();
		}
		arr[vector_size] = std::move(val);
		++vector_size;
	}

	template <typename T>
	void vector<T>::pop_back() {
		--vector_size;
		arr[vector_size].~T();
	}


	template <typename T>
	template <class ... Args>
	typename vector<T>::iterator vector<T>::emplace(typename vector<T>::const_iterator it, Args && ... args) {
		iterator iit = &arr[it - arr];
		if (vector_size == reserved_size) {
			reserved_size <<= 2;
			reallocate();
		}
		memmove(iit + 1, iit, (vector_size - (it - arr)) * sizeof(T));
		(*iit) = std::move(T(std::forward<Args>(args) ...));
		++vector_size;
		return iit;
	}

	template <typename T>
	typename vector<T>::iterator vector<T>::insert(typename vector<T>::const_iterator it, const T &val) {
		iterator iit = &arr[it - arr];
		if (vector_size == reserved_size) {
			reserved_size <<= 2;
			reallocate();
		}
		memmove(iit + 1, iit, (vector_size - (it - arr)) * sizeof(T));
		(*iit) = val;
		++vector_size;
		return iit;
	}

	template <typename T>
	typename vector<T>::iterator vector<T>::insert(typename vector<T>::const_iterator it, T &&val) {
		iterator iit = &arr[it - arr];
		if (vector_size == reserved_size) {
			reserved_size <<= 2;
			reallocate();
		}
		memmove(iit + 1, iit, (vector_size - (it - arr)) * sizeof(T));
		(*iit) = std::move(val);
		++vector_size;
		return iit;
	}

	template <typename T>
	typename vector<T>::iterator vector<T>::insert(typename vector<T>::const_iterator it, typename vector<T>::size_type cnt, const T &val) {
		iterator f = &arr[it - arr];
		if (!cnt) return f;
		if (vector_size + cnt > reserved_size) {
			reserved_size = (vector_size + cnt) << 2;
			reallocate();
		}
		memmove(f + cnt, f, (vector_size - (it - arr)) * sizeof(T));
		vector_size += cnt;
		for (iterator it = f; cnt--; ++it)
			(*it) = val;
		return f;
	}

	template <typename T>
	template <class InputIt>
	typename vector<T>::iterator vector<T>::insert(typename vector<T>::const_iterator it, InputIt first, InputIt last) {
		iterator f = &arr[it - arr];
		size_type cnt = last - first;
		if (!cnt) return f;
		if (vector_size + cnt > reserved_size) {
			reserved_size = (vector_size + cnt) << 2;
			reallocate();
		}
		memmove(f + cnt, f, (vector_size - (it - arr)) * sizeof(T));
		for (iterator it = f; first != last; ++it, ++first)
			(*it) = *first;
		vector_size += cnt;
		return f;
	}

	template <typename T>
	typename vector<T>::iterator vector<T>::insert(typename vector<T>::const_iterator it, std::initializer_list<T> lst) {
		size_type cnt = lst.size();
		iterator f = &arr[it - arr];
		if (!cnt) return f;
		if (vector_size + cnt > reserved_size) {
			reserved_size = (vector_size + cnt) << 2;
			reallocate();
		}
		memmove(f + cnt, f, (vector_size - (it - arr)) * sizeof(T));
		iterator iit = f;
		for (auto &item : lst) {
			(*iit) = item;
			++iit;
		}
		vector_size += cnt;
		return f;
	}

	template <typename T>
	typename vector<T>::iterator vector<T>::erase(typename vector<T>::const_iterator it) {
		iterator iit = &arr[it - arr];
		(*iit).~T();
		memmove(iit, iit + 1, (vector_size - (it - arr) - 1) * sizeof(T));
		--vector_size;
		return iit;
	}

	template <typename T>
	typename vector<T>::iterator vector<T>::erase(typename vector<T>::const_iterator first, typename vector<T>::const_iterator last) {
		iterator f = &arr[first - arr];
		if (first == last) return f;
		for (; first != last; ++first)
			(*first).~T();
		memmove(f, last, (vector_size - (last - arr)) * sizeof(T));
		vector_size -= last - first;
		return f;
	}

	template <typename T>
	void vector<T>::swap(vector<T> &rhs) {
		size_t tvector_size = vector_size,
			treserved_size = reserved_size;
		T *tarr = arr;

		vector_size = rhs.vector_size;
		reserved_size = rhs.reserved_size;
		arr = rhs.arr;

		rhs.vector_size = tvector_size;
		rhs.reserved_size = treserved_size;
		rhs.arr = tarr;
	}

	template <typename T>
	void vector<T>::clear() noexcept {
		size_type i;
		for (i = 0; i < vector_size; ++i)
			arr[i].~T();
		vector_size = 0;
	}


	template <typename T>
	bool vector<T>::operator == (const vector<T> &rhs) const {
		if (vector_size != rhs.vector_size) return false;
		size_type i;
		for (i = 0; i < vector_size; ++i)
			if (arr[i] != rhs.arr[i])
				return false;
		return true;
	}

	template <typename T>
	bool vector<T>::operator != (const vector<T> &rhs) const {
		if (vector_size != rhs.vector_size) return true;
		size_type i;
		for (i = 0; i < vector_size; ++i)
			if (arr[i] != rhs.arr[i])
				return true;
		return false;
	}

	template <typename T>
	bool vector<T>::operator < (const vector<T> &rhs) const {
		size_type i, j, ub = vector_size < rhs.vector_size ? vector_size : rhs.vector_size;
		for (i = 0; i < ub; ++i)
			if (arr[i] != rhs.arr[i])
				return arr[i] < rhs.arr[i];
		return vector_size < rhs.vector_size;
	}

	template <typename T>
	bool vector<T>::operator <= (const vector<T> &rhs) const {
		size_type i, j, ub = vector_size < rhs.vector_size ? vector_size : rhs.vector_size;
		for (i = 0; i < ub; ++i)
			if (arr[i] != rhs.arr[i])
				return arr[i] < rhs.arr[i];
		return vector_size <= rhs.vector_size;
	}

	template <typename T>
	bool vector<T>::operator > (const vector<T> &rhs) const {
		size_type i, j, ub = vector_size < rhs.vector_size ? vector_size : rhs.vector_size;
		for (i = 0; i < ub; ++i)
			if (arr[i] != rhs.arr[i])
				return arr[i] > rhs.arr[i];
		return vector_size > rhs.vector_size;
	}

	template <typename T>
	bool vector<T>::operator >= (const vector<T> &rhs) const {
		size_type i, j, ub = vector_size < rhs.vector_size ? vector_size : rhs.vector_size;
		for (i = 0; i < ub; ++i)
			if (arr[i] != rhs.arr[i])
				return arr[i] > rhs.arr[i];
		return vector_size >= rhs.vector_size;
	}

	template <>
	void vector<int>::resize(typename vector<int>::size_type sz) {
		if (sz > reserved_size) {
			reserved_size = sz;
			reallocate();
		}
		vector_size = sz;
	}

	template <>
	void vector<float>::resize(typename vector<float>::size_type sz) {
		if (sz > reserved_size) {
			reserved_size = sz;
			reallocate();
		}
		vector_size = sz;
	}

	template <>
	void vector<double>::resize(typename vector<double>::size_type sz) {
		if (sz > reserved_size) {
			reserved_size = sz;
			reallocate();
		}
		vector_size = sz;
	}

	template <>
	void vector<int>::resize(typename vector<int>::size_type sz, const int &c) {
		if (sz > vector_size) {
			if (sz > reserved_size) {
				reserved_size = sz;
				reallocate();
			}
			size_type i;
			for (i = vector_size; i < sz; ++i)
				arr[i] = c;
		}
		vector_size = sz;
	}

	template <>
	void vector<float>::resize(typename vector<float>::size_type sz, const float &c) {
		if (sz > vector_size) {
			if (sz > reserved_size) {
				reserved_size = sz;
				reallocate();
			}
			size_type i;
			for (i = vector_size; i < sz; ++i)
				arr[i] = c;
		}
		vector_size = sz;
	}

	template <>
	void vector<double>::resize(typename vector<double>::size_type sz, const double &c) {
		if (sz > vector_size) {
			if (sz > reserved_size) {
				reserved_size = sz;
				reallocate();
			}
			size_type i;
			for (i = vector_size; i < sz; ++i)
				arr[i] = c;
		}
		vector_size = sz;
	}

	template <>
	void vector<int>::pop_back() {
		--vector_size;
	}

	template <>
	void vector<float>::pop_back() {
		--vector_size;
	}

	template <>
	void vector<double>::pop_back() {
		--vector_size;
	}

	template <>
	typename vector<int>::iterator vector<int>::erase(typename vector<int>::const_iterator it) {
		iterator iit = &arr[it - arr];
		memmove(iit, iit + 1, (vector_size - (it - arr) - 1) * sizeof(int));
		--vector_size;
		return iit;
	}

	template <>
	typename vector<float>::iterator vector<float>::erase(typename vector<float>::const_iterator it) {
		iterator iit = &arr[it - arr];
		memmove(iit, iit + 1, (vector_size - (it - arr) - 1) * sizeof(float));
		--vector_size;
		return iit;
	}

	template <>
	typename vector<double>::iterator vector<double>::erase(typename vector<double>::const_iterator it) {
		iterator iit = &arr[it - arr];
		memmove(iit, iit + 1, (vector_size - (it - arr) - 1) * sizeof(double));
		--vector_size;
		return iit;
	}

	template <>
	typename vector<bool>::iterator vector<bool>::erase(typename vector<bool>::const_iterator first, typename vector<bool>::const_iterator last) {
		iterator f = &arr[first - arr];
		if (first == last) return f;
		memmove(f, last, (vector_size - (last - arr)) * sizeof(bool));
		vector_size -= last - first;
		return f;
	}

	template <>
	typename vector<int>::iterator vector<int>::erase(typename vector<int>::const_iterator first, typename vector<int>::const_iterator last) {
		iterator f = &arr[first - arr];
		if (first == last) return f;
		memmove(f, last, (vector_size - (last - arr)) * sizeof(int));
		vector_size -= last - first;
		return f;
	}

	template <>
	typename vector<float>::iterator vector<float>::erase(typename vector<float>::const_iterator first, typename vector<float>::const_iterator last) {
		iterator f = &arr[first - arr];
		if (first == last) return f;
		memmove(f, last, (vector_size - (last - arr)) * sizeof(float));
		vector_size -= last - first;
		return f;
	}

	template <>
	typename vector<double>::iterator vector<double>::erase(typename vector<double>::const_iterator first, typename vector<double>::const_iterator last) {
		iterator f = &arr[first - arr];
		if (first == last) return f;
		memmove(f, last, (vector_size - (last - arr)) * sizeof(double));
		vector_size -= last - first;
		return f;
	}

	template <>
	void vector<int>::clear() noexcept {
		vector_size = 0;
	}

	template <>
	void vector<float>::clear() noexcept {
		vector_size = 0;
	}

	template <>
	void vector<double>::clear() noexcept {
		vector_size = 0;
	}