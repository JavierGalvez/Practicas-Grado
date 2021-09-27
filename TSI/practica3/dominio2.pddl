(define (domain starcraft)
    (:requirements :strips :typing :adl)
    (:types
        Localizacion 
        Unidad Edificio Recurso - object
    )
    (:constants
        CentroDeMando Barracones Extractor - tipoEdificio
        VCE - tipoUnidad
        Mineral Gas - tipoRecurso
    )
    (:predicates
        (en ?obj - object ?l - Localizacion)
        (conectado ?i - Localizacion ?j - Localizacion)
        (extrayendo ?u - Unidad ?r - Recurso)
        (tipoEdificio ?e - Edificio ?t - tipoEdificio)
        (tipoUnidad ?u - Unidad ?t - tipoUnidad)
        (tipoRecurso ?r - Recurso ?t - tipoRecurso)
        (necesita ?e - Edificio ?r - tipoRecurso)
        (recursoDisponible ?r - tipoRecurso)
    )
    (:action Navegar
        :parameters (?u - Unidad ?x ?y - Localizacion)
        :precondition
            (and
                (en ?u ?x)
                (conectado ?x ?y)
                (not (exists (?r - Recurso) (extrayendo ?u ?r)))
            )
        :effect
            (and
                (en ?u ?y)
                (not (en ?u ?x))
            )
    )
    (:action Asignar
        :parameters (?u - Unidad ?r - Recurso)
        :precondition
            (and
                (tipoUnidad ?u VCE)
                (not (exists (?r2 - Recurso) (extrayendo ?u ?r2)))
                (exists (?l - Localizacion)
                    (and
                        (en ?r ?l)
                        (en ?u ?l)
                        
                        ;Solo se puede asignar a un nodo de Gas si hay un Extractor construido
                        (imply (tipoRecurso ?r Gas) 
                            (exists (?e - Edificio) 
                                (and 
                                    (tipoEdificio ?e Extractor) 
                                    (en ?e ?l)
                                )
                            )
                        )
                    )
                )
            )
        :effect
            (and
                (extrayendo ?u ?r)
                (when (tipoRecurso ?r Mineral) (and (recursoDisponible Mineral)))
                (when (tipoRecurso ?r Gas) (and (recursoDisponible Gas)))
            )
    )
    (:action Construir
        :parameters (?u - Unidad ?e - Edificio ?l - Localizacion)
        :precondition
            (and
                ;No hay un edificio construido ya en ese sitio
                (not (exists (?e2 - Edificio) (en ?e2 ?l)))

                ;No esta construido ese edificio en otro lugar
                (not (exists (?l2 - Localizacion) (en ?e ?l2)))

                ;Solo un VCE puede construir
                (tipoUnidad ?u VCE)

                ;El VCE esta libre
                (not (exists (?r - Recurso) (extrayendo ?u ?r)))
                
                ;Comprobamos que tenemos todos los recursos necesarios
                (forall (?r - tipoRecurso)
                    (imply
                        (necesita ?e ?r)
                        (recursoDisponible ?r)
                    )
                )

                ;Solo se puede construir un Extractor en una localizacion con Gas
                (imply (tipoEdificio ?e Extractor)
                    (exists (?r - Recurso)
                        (and 
                            (tipoRecurso ?r Gas)
                            (en ?r ?l)
                        )
                    )
                )
                (en ?u ?l)
            )
        :effect
            (and
                (en ?e ?l)
            )
    )
)
