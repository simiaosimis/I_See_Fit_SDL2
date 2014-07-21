template <class Type>
int Math::sign(const Type number_) {
    if (number_ >= 0) {
        return 1;
    }
    else {
        return -1;
    }
}
