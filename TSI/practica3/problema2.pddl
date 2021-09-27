(define (problem ejer2)
    (:domain starcraft)
    (:objects
        vce1 vce2 vce3 - Unidad
        centroDeMando1 barracones1 extractor1 - Edificio
        mineral1 mineral2 mineral3 gas1 gas2 - Recurso
        loc1_1 loc1_2 loc1_3 loc1_4 loc1_5 loc2_1 loc2_2 loc2_3 loc2_4 loc2_5 loc3_1 loc3_2 loc3_3 loc3_4 loc3_5 loc4_1 loc4_2 loc4_3 loc4_4 loc4_5 loc5_1 loc5_2 loc5_3 loc5_4 loc5_5 - Localizacion
    )
    (:init
        (conectado loc1_1 loc2_1)
        (conectado loc1_1 loc1_2)
        (conectado loc1_2 loc2_2)
        (conectado loc1_2 loc1_3)
        (conectado loc1_2 loc1_1)
        (conectado loc1_3 loc2_3)
        (conectado loc1_3 loc1_4)
        (conectado loc1_3 loc1_2)
        (conectado loc1_4 loc2_4)
        (conectado loc1_4 loc1_5)
        (conectado loc1_4 loc1_3)
        (conectado loc1_5 loc2_5)
        (conectado loc1_5 loc1_4)
        (conectado loc2_1 loc1_1)
        (conectado loc2_1 loc3_1)
        (conectado loc2_1 loc2_2)
        (conectado loc2_2 loc1_2)
        (conectado loc2_2 loc3_2)
        (conectado loc2_2 loc2_3)
        (conectado loc2_2 loc2_1)
        (conectado loc2_3 loc1_3)
        (conectado loc2_3 loc3_3)
        (conectado loc2_3 loc2_4)
        (conectado loc2_3 loc2_2)
        (conectado loc2_4 loc1_4)
        (conectado loc2_4 loc3_4)
        (conectado loc2_4 loc2_5)
        (conectado loc2_4 loc2_3)
        (conectado loc2_5 loc1_5)
        (conectado loc2_5 loc3_5)
        (conectado loc2_5 loc2_4)
        (conectado loc3_1 loc2_1)
        (conectado loc3_1 loc4_1)
        (conectado loc3_1 loc3_2)
        (conectado loc3_2 loc2_2)
        (conectado loc3_2 loc4_2)
        (conectado loc3_2 loc3_3)
        (conectado loc3_2 loc3_1)
        (conectado loc3_3 loc2_3)
        (conectado loc3_3 loc4_3)
        (conectado loc3_3 loc3_4)
        (conectado loc3_3 loc3_2)
        (conectado loc3_4 loc2_4)
        (conectado loc3_4 loc4_4)
        (conectado loc3_4 loc3_5)
        (conectado loc3_4 loc3_3)
        (conectado loc3_5 loc2_5)
        (conectado loc3_5 loc4_5)
        (conectado loc3_5 loc3_4)
        (conectado loc4_1 loc3_1)
        (conectado loc4_1 loc5_1)
        (conectado loc4_1 loc4_2)
        (conectado loc4_2 loc3_2)
        (conectado loc4_2 loc5_2)
        (conectado loc4_2 loc4_3)
        (conectado loc4_2 loc4_1)
        (conectado loc4_3 loc3_3)
        (conectado loc4_3 loc5_3)
        (conectado loc4_3 loc4_4)
        (conectado loc4_3 loc4_2)
        (conectado loc4_4 loc3_4)
        (conectado loc4_4 loc5_4)
        (conectado loc4_4 loc4_5)
        (conectado loc4_4 loc4_3)
        (conectado loc4_5 loc3_5)
        (conectado loc4_5 loc5_5)
        (conectado loc4_5 loc4_4)
        (conectado loc5_1 loc4_1)
        (conectado loc5_1 loc5_2)
        (conectado loc5_2 loc4_2)
        (conectado loc5_2 loc5_3)
        (conectado loc5_2 loc5_1)
        (conectado loc5_3 loc4_3)
        (conectado loc5_3 loc5_4)
        (conectado loc5_3 loc5_2)
        (conectado loc5_4 loc4_4)
        (conectado loc5_4 loc5_5)
        (conectado loc5_4 loc5_3)
        (conectado loc5_5 loc4_5)
        (conectado loc5_5 loc5_4)

        (tipoUnidad vce1 VCE)
        (tipoUnidad vce2 VCE)
        (tipoUnidad vce3 VCE)
        (tipoEdificio centroDeMando1 CentroDeMando)
        (tipoEdificio barracones1 Barracones)
        (tipoEdificio extractor1 Extractor)
        (tipoRecurso mineral1 Mineral)
        (tipoRecurso mineral2 Mineral)
        (tipoRecurso mineral3 Mineral)
        (tipoRecurso gas1 Gas)
        (tipoRecurso gas2 Gas)

        (en vce1 loc3_3)
        (en vce2 loc3_3)
        (en vce3 loc3_3)

        (en centroDeMando1 loc3_3)

        (en gas1 loc1_1)
        (en mineral1 loc2_1)
        (en mineral2 loc3_1)
        (en mineral3 loc4_1)
        (en gas2 loc5_1)

        (necesita barracones1 Mineral)
        (necesita centroDeMando1 Gas)
        (necesita extractor1 Mineral)
    )
    (:goal
        (and
            (recursoDisponible Gas)
            (exists (?l - Localizacion) (en barracones1 ?l))
        )
    )
)
