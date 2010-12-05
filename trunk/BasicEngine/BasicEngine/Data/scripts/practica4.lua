-- vim:ts=4:et:
--REQUIRES--
--DECLARACI�N DE VARIABLES GLOBALES--
-- Array de Estados para el personaje i-esimo --
gaSTATES = {0} -- Un personaje con estado inicial 1
gTARGETS = {
            {{3, 0, 3}, {-3, 0, 3}, {-3, 0, -3}, {3, 0, -3}} -- Personaje 1
            }

--DEFINICI�N DE FUNCIONES--

function NextEndPoint(lId)
    -- Obtiene los estados del personaje
    local lTargets = gTARGETS[lId]

    -- Actualiza el estado del personaje lId-esimo (de forma c�clica)
    gaSTATES[lId] = 1 + gaSTATES[lId] % #lTargets

    -- Ahora obtiene su nueva posicion
    local lNewTarget = lTargets[gaSTATES[lId]]

    -- Ahora actualiza el objetivo en el personaje
    print("Nuevo objetivo para ID " .. lId .. ": " ..
        lNewTarget[1] .. ", " .. lNewTarget[2] .. ", " .. lNewTarget[3])
    SetPatrolTarget(lId, lNewTarget[1], lNewTarget[2], lNewTarget[3])
end

--C�DIGO LUA--
print("Practica 4")
value = CreatePatrol(2, 0, 1, 1, 1)
print("ID del personaje " .. value)


