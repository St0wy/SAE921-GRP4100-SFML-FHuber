#include <SFML/Graphics.hpp>

#include <chrono>
#include <random>

constexpr int WINDOW_WIDTH = 800;
constexpr int WINDOW_HEIGHT = 600;
constexpr int FRAMERATE = 60;

constexpr int MIN_BROWN = 10;
constexpr int MAX_BROWN = 30;
constexpr int MIN_VIOLET = 100;
constexpr int MAX_VIOLET = 150;
constexpr int MIN_YELLOW = 150;
constexpr int MAX_YELLOW = 170;
constexpr int MIN_RED = 160;
constexpr int MAX_RED = 180;

void create_rectangles(std::vector<sf::RectangleShape>& rectangles, std::default_random_engine& gen);
void create_rectangle_type(
	std::vector<sf::RectangleShape>& rectangles,
	std::default_random_engine& gen,
	const sf::Color& color,
	const std::uniform_real_distribution<float>& size_distrib,
	const int rectangle_count);

int main()
{
	// obtain a seed from the system clock
	const uint32_t seed = static_cast<uint32_t>(
		std::chrono::high_resolution_clock::now().time_since_epoch().count());
	std::default_random_engine gen(seed);

	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Mondrian Picture");

	std::vector<sf::RectangleShape> rectangles;

	create_rectangles(rectangles, gen);

	// Basic Setup of the window
	// Vertical sync, framerate
	window.setVerticalSyncEnabled(true);
	window.setFramerateLimit(FRAMERATE);

	while (window.isOpen())
	{
		// on inspecte tous les évènements de la fenêtre qui ont été émis depuis
		// la précédente itération
		sf::Event event{};

		while (window.pollEvent(event))
		{
			switch (event.type)  // NOLINT(clang-diagnostic-switch-enum)
			{
				// évènement "fermeture demandée" : on ferme la fenêtre
			case sf::Event::Closed:
				window.close();
				break;
			default:
				break;
			}
		}

		// Graphical Region
		window.clear(sf::Color::White);

		// Render
		for (const auto& rectangle : rectangles)
		{
			window.draw(rectangle);
		}

		sf::RectangleShape rect(sf::Vector2f(100, 100));
		rect.setFillColor(sf::Color::Red);
		//window.draw(rect);

		window.display();
	}
}

void create_rectangles(std::vector<sf::RectangleShape>& rectangles, std::default_random_engine& gen)
{
	const sf::Color yellow(252, 178, 50);
	const sf::Color red(252, 35, 82);
	const sf::Color violet(141, 95, 211);
	const sf::Color brown(140, 83, 18);

	const std::uniform_int_distribution brown_distrib(25, 30);
	const std::uniform_int_distribution yellow_distrib(8, 10);
	const std::uniform_int_distribution red_distrib(3, 6);
	const std::uniform_int_distribution violet_distrib(6, 10);

	const int yellow_count = yellow_distrib(gen);
	const int red_count = red_distrib(gen);
	const int violet_count = violet_distrib(gen);
	const int brown_count = brown_distrib(gen);

	const int total_rectangles_count = yellow_count + red_count + violet_count + brown_count;

	rectangles.clear();
	rectangles.reserve(total_rectangles_count);

	const std::uniform_real_distribution<float> brown_size_distrib(MIN_BROWN, MAX_BROWN);
	const std::uniform_real_distribution<float> yellow_size_distrib(MIN_YELLOW, MAX_YELLOW);
	const std::uniform_real_distribution<float> red_size_distrib(MIN_RED, MAX_RED);
	const std::uniform_real_distribution<float> violet_size_distrib(MIN_VIOLET, MAX_VIOLET);

	create_rectangle_type(rectangles, gen, yellow, yellow_size_distrib, yellow_count);
	create_rectangle_type(rectangles, gen, violet, violet_size_distrib, violet_count);
	create_rectangle_type(rectangles, gen, red, red_size_distrib, red_count);
	create_rectangle_type(rectangles, gen, brown, brown_size_distrib, brown_count);
}

/**
 * \brief Adds a certain amount of a certain type of rectangle in the vector.
 * \param rectangles Vector to add the rectangles in.
 * \param gen Random number generator.
 * \param color Color of the rectangles.
 * \param size_distrib Size distribution of the rectangles.
 * \param rectangle_count The number of rectangles to add.
 */
void create_rectangle_type(
	std::vector<sf::RectangleShape>& rectangles,
	std::default_random_engine& gen,
	const sf::Color& color,
	const std::uniform_real_distribution<float>& size_distrib,
	const int rectangle_count)
{
	const std::uniform_int_distribution screen_distrib_x(0, WINDOW_WIDTH - 1);
	const std::uniform_int_distribution screen_distrib_y(0, WINDOW_HEIGHT - 1);

	for (int i = 0; i < rectangle_count; ++i)
	{
		const float x_size = size_distrib(gen);
		const float y_size = size_distrib(gen);
		const auto x_pos = static_cast<float>(screen_distrib_x(gen));
		const auto y_pos = static_cast<float>(screen_distrib_y(gen));

		sf::RectangleShape rectangle(sf::Vector2f(x_size, y_size));
		rectangle.setFillColor(color);
		rectangle.setPosition(x_pos, y_pos);
		rectangle.setSize(sf::Vector2f(x_size, y_size));

		rectangles.emplace_back(rectangle);
	}

}