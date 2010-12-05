-- vim:ts=4:et:
--REQUIRES--
--DECLARACIÓN DE VARIABLES GLOBALES--
-- Array de Estados para el personaje i-esimo --
gaSTATES = {0} -- Un personaje con estado inicial 1
gTARGETS = {
            {{3, 0, 3}, {-3, 0, 3}, {-3, 0, -3}, {3, 0, -3}} -- Personaje 1
            }

--DEFINICIÓN DE FUNCIONES--
-- Dibuja el path de un personaje 
function DrawPathFor(lId)
    local lRuta = gTARGETS[lId]
    local i

    for i = 1, #lRuta - 1 do
        local lA = lRuta[i]
        local lB = lRuta[i + 1]
        DrawLine(lA[1], lA[2], lA[3], lB[1], lB[2], lB[3])
    end

    lA = lRuta[#lRuta]
    lB = lRuta[1]
    DrawLine(lA[1], lA[2], lA[3], lB[1], lB[2], lB[3])
end


-- Dibuja el path de todos los personajes
function DrawPath()
    local i

    for i = 1, #gaSTATES do
        DrawPathFor(i)
    end
end


function NextEndPoint(lId)
    -- Obtiene los estados del personaje
    local lTargets = gTARGETS[lId]

    -- Actualiza el estado del personaje lId-esimo (de forma cíclica)
    gaSTATES[lId] = 1 + gaSTATES[lId] % #lTargets

    -- Ahora obtiene su nueva posicion
    local lNewTarget = lTargets[gaSTATES[lId]]

    DrawPath(lId)

    -- Ahora actualiza el objetivo en el personaje
    print("Nuevo objetivo para ID " .. lId .. ": " ..
        lNewTarget[1] .. ", " .. lNewTarget[2] .. ", " .. lNewTarget[3])
    SetPatrolTarget(lId, lNewTarget[1], lNewTarget[2], lNewTarget[3])
end

--CÓDIGO LUA--
print("Practica 4")
value = CreatePatrol(2, 0, 1, 1, 1)
print("ID del personaje " .. value)


