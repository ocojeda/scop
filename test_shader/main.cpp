#include "Shader.h"

void SceneOpenGL::bouclePrincipale()
{
    // Variables

    bool terminer(false);
    float vertices[] = {-0.5, -0.5,   0.0, 0.5,   0.5, -0.5};

    Shader shaderBasique("Shaders/basique_2D.vert", "Shaders/basique.frag");
    shaderBasique.charger();


    // Boucle principale

    while(!terminer)
    {
        // Gestion des évènements

        SDL_WaitEvent(&m_evenements);

        if(m_evenements.window.event == SDL_WINDOWEVENT_CLOSE)
            terminer = true;


        // Nettoyage de l'écran

        glClear(GL_COLOR_BUFFER_BIT);


        // Activation du shader

        glUseProgram(shaderBasique.getProgramID());


            // On remplie puis on active le tableau Vertex Attrib 0

            glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, vertices);
            glEnableVertexAttribArray(0);


            // Affichage du triangle

            glDrawArrays(GL_TRIANGLES, 0, 3);


            // On désactive le tableau Vertex Attrib puisque l'on n'en a plus besoin

            glDisableVertexAttribArray(0);


        // Désactivation du shader

        glUseProgram(0);


        // Actualisation de la fenêtre

        SDL_GL_SwapWindow(m_fenetre);
    }
}