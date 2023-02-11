#ifndef S21_FLAGS_HPP
#define S21_FLAGS_HPP

//namespace s21 {
//	template <typename Enum>
//	class Flags
//	{
//		static_assert((sizeof(Enum) <= sizeof(int)), "QFlags uses an int as storage, so an enum with underlying long long will overflow.");
//		static_assert((std::is_enum<Enum>::value)), "Flags is only usable on enumeration types.");
//
//	};
//}
#include <cstdint>
#include <type_traits>

namespace s21 {
	template <typename Enum>
	class Flags {

	};
}

enum AnimalFlags : uint8_t
{
	HasClaws = 1,
	CanFly = 2,
	EatsFish = 4,
	Endangered = 8
};

enum class PlantFlags : uint8_t
{
	HasLeaves = 1,
	HasFlowers = 2,
	HasFruit = 4,
	HasThorns = 8
};

//DECLARE_FLAGS(AnimalFlagsTest, AnimalFlags)
typedef s21::Flags<AnimalFlags> Animal;

int main()
{
	Animal seahawk = Animal::CanFly;        // Compiles, as expected
	Animal lion = Animal::HasClaws;         // Compiles, as expected
	PlantFlags rose = PlantFlags::HasFlowers;         // Compiles, as expected
//  rose = 1;                                         // Won't compile, as expected
	if (seahawk != lion) {}                           // Compiles, as expected
//  if (seahawk == rose) {}                           // Won't compile, as expected
//  seahawk = PlantFlags::HasThorns;                  // Won't compile, as expected
	seahawk = seahawk | Animal::EatsFish;        // Compiles, as expected
	lion = Animal::HasClaws |                    // Compiles, as expected
			Animal::Endangered;
//  int eagle = AnimalFlags::CanFly |                 // Won't compile, as expected
//              AnimalFlags::HasClaws;
//  int has_claws = seahawk & AnimalFlags::CanFly;    // Won't compile, as expected
	if (seahawk & Animal::CanFly) {}             // Compiles, as expected
	seahawk = seahawk & Animal::CanFly;          // Compiles, as expected

	return 0;
}

#endif
