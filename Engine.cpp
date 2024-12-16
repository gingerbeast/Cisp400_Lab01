#include "Engine.h"

Engine::Engine() : m_Window(VideoMode(800, 600), "Particle Engine") {}

void Engine::input()
{
    Event event;
    while (m_Window.pollEvent(event))
    {
        if (event.type == Event::Closed)
            m_Window.close();

        if (Mouse::isButtonPressed(Mouse::Left))
        {
            Vector2i mousePos = Mouse::getPosition(m_Window);
            m_particles.emplace_back(m_Window, 10, mousePos);
        }
    }
}

void Engine::update(float dtAsSeconds)
{
    for (auto it = m_particles.begin(); it != m_particles.end();)
    {
        it->update(dtAsSeconds);
        if (it->getTTL() <= 0)
            it = m_particles.erase(it);
        else
            ++it;
    }
}

void Engine::draw()
{
    m_Window.clear();
    for (const auto& particle : m_particles)
        m_Window.draw(particle);
    m_Window.display();
}

void Engine::run()
{
    Clock clock;

    while (m_Window.isOpen())
    {
        Time dt = clock.restart();
        input();
        update(dt.asSeconds());
        draw();
    }
}
