export module fox.core.types.circular_buffer;

import std;

import fox.core.types.common;

export namespace fox
{
    template<typename T, fox::size_t N>
    class CircularBuffer
    {
    public:
        CircularBuffer() = default;

        constexpr auto push_back(T&& value) -> T&
        {
            auto previous = index_;

            array_.at(index_++)  = std::move(value);
            index_              %= array_.size();
            capacity_            = std::min(++capacity_, array_.size());

            return array_.at(previous);
        }

        constexpr auto at       (fox::size_t index)
        {
            return array_.at(index);
        }
        constexpr auto at       (fox::size_t index) const
        {
            return array_.at(index);
        }
        
        constexpr auto begin    (this auto& self) noexcept
        {
            return std::ranges::begin(self.array_);
        }
        constexpr auto end      (this auto& self) noexcept
        {
            return std::ranges::end(self.array_);
        }
        
        constexpr auto size     () const noexcept
        {
            return capacity_;
        }
        constexpr auto capacity () const noexcept
        {
            return array_.size();
        }

    private:
        std::array<T, N> array_{};
        fox::size_t      index_{};
        fox::size_t      capacity_{};
    };
}
