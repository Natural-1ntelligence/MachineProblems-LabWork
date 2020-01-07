
class ListIterator : public std::iterator<std::bidirectional_iterator_tag, T> {
  private:
    ListNode* position_;

  public:
    ListIterator() : position_(NULL) { }
    ListIterator(ListNode* x) : position_(x) { }

    // Pre-Increment, ++iter
    ListIterator& operator++() {
        // @: graded in MP3.1   DONE
        position_ = position_->next;
        return *this;
    }

    // Post-Increment, iter++
    ListIterator operator++(int) {
        // @: graded in MP3.1    DONE
        ListNode* hold = position_;
        position_ = position_->next;
        return ListIterator(hold);  //changed NULL to hold
    }

    // Pre-Decrement, --iter
    ListIterator& operator--() {
        // @: graded in MP3.1   DONE
        position_ = position_->prev;
        return *this;
    }

    // Post-Decrement, iter--
    ListIterator operator--(int) {
        // @: graded in MP3.1  DONE
        ListNode* hold = position_;
        position_ = position_->prev;
        return ListIterator(hold);
    }

    bool operator!=(const ListIterator& rhs) {
        // @: graded in MP3.1  DONE
        if(this->position_ != rhs.position_) {return true;}
        else {return false;}
    }

    bool operator==(const ListIterator& rhs) {
        return !(*this != rhs);
    }

    const T& operator*() {
        return position_->data;
    }

    const T* operator->() {
        return &(position_->data);
    }
};
