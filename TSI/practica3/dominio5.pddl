(define (domain starcraft)
    (:requirements :strips :typing :adl)
    (:types
        Localizacion 
        Unidad Edificio Recurso - object
        tipoEdificio tipoUnidad Investigacion - necesitanRecursos
    )

    (:constants
        CentroDeMando Barracones Extractor Bahia_de_Ingenieria - tipoEdificio
        VCE Marine Segador - tipoUnidad
        Mineral Gas - tipoRecurso
        Impulsor_Segador - Investigacion
    )

    (:predicates
        (en ?obj - object ?l - Localizacion)
        (conectado ?i - Localizacion ?j - Localizacion)
        (extrayendo ?u - Unidad ?r - Recurso)
        (tipoEdificio ?e - Edificio ?t - tipoEdificio)
        (tipoUnidad ?u - Unidad ?t - tipoUnidad)
        (tipoRecurso ?r - Recurso ?t - tipoRecurso)
        (necesita ?n - necesitanRecursos ?r - tipoRecurso)
        (recursoDisponible ?r - tipoRecurso)
        (reclutarEn ?u - tipoUnidad ?e - tipoEdificio)
        (investigado ?i - Investigacion)
        (necesitaInvestigacion ?u - tipoUnidad ?i - Investigacion)
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
                (exists (?te - tipoEdificio) 
                    (and
                        (tipoEdificio ?e ?te)
                        (forall (?r - tipoRecurso)
                            (imply
                                ;Comprobamos si necesita el recurso ?r
                                (necesita ?te ?r)
                                ;Si lo necesita debe estar disponible
                                (recursoDisponible ?r)
                            )
                        )
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

    (:action Reclutar
        :parameters (?u - Unidad ?e - Edificio ?l - Localizacion)
        :precondition
            (and
                ;La unidad no ha sido reclutada todavia
                (not (exists (?l2 - Localizacion) (en ?u ?l2)))

                (exists (?t - tipoUnidad) 
                    (and
                        (tipoUnidad ?u ?t)

                        ;Comprobamos que tenemos todos los recursos necesarios
                        (forall (?r - tipoRecurso)
                            (imply
                                ;Comprobamos si necesita el recurso ?r
                                (necesita ?t ?r)
                                ;Si lo necesita debe estar disponible
                                (recursoDisponible ?r)
                            )
                        )

                        ;Comprobamos que la unidad se puede reclutar en ese tipo de edificio
                        (exists (?te - tipoEdificio)
                            (and
                                (tipoEdificio ?e ?te)
                                (reclutarEn ?t ?te)
                            )
                        )

                        ;Comprobamos que tenemos todas las investigaciones necesarias
                        (forall (?i - Investigacion)
                            (imply
                                ;Comprobamos si necesita la investigacion ?i
                                (necesitaInvestigacion ?t ?i)
                                ;Si la necesita debe estar investigada ya
                                (investigado ?i)
                            )
                        )
                    )
                )
                (en ?e ?l)
            )
        :effect
            (and
                (en ?u ?l)
            )
    )

    (:action Investigar
        :parameters (?i - Investigacion ?e - Edificio)
        :precondition
            (and
                ;Comprobamos que no este ya investigado
                (not (investigado ?i))

                ;Comprobamos el edificio donde se va a investigar es una bahia y esta construida
                (tipoEdificio ?e Bahia_de_Ingenieria)
                (exists (?l - Localizacion) (en ?e ?l))

                ;Comprobamos que tenemos todos los recursos necesarios
                (forall (?r - tipoRecurso)
                    (imply
                        ;Comprobamos si necesita el recurso ?r
                        (necesita ?i ?r)
                        ;Si lo necesita debe estar disponible
                        (recursoDisponible ?r)
                    )
                )
            )
        :effect
            (and
                (investigado ?i)
            )
    )
)
