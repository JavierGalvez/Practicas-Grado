(define (domain starcraft)
    (:requirements :strips :typing :adl :fluents)
    (:types
        Localizacion 
        Unidad Edificio Recurso - object
        tipoEdificio tipoUnidad Investigacion - necesitanRecursos
    )

    (:constants
        CentroDeMando Barracones Extractor Bahia_de_Ingenieria Deposito - tipoEdificio
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
        (reclutarEn ?u - tipoUnidad ?e - tipoEdificio)
        (investigado ?i - Investigacion)
        (necesitaInvestigacion ?u - tipoUnidad ?i - Investigacion)
    )

    (:functions
        (recursoDisponible ?r - tipoRecurso)
        (necesita ?n - necesitanRecursos ?r - tipoRecurso)
        (maxCapacidad)
        (vceExtrayendo ?r - tipoRecurso)
        (cantidadRecolectada)
        (tiempo ?n - necesitanRecursos)
        (velocidad ?u - tipoUnidad)
        (tiempoTotal)
    )

    (:action Navegar
        :parameters (?u - Unidad ?t - tipoUnidad ?x ?y - Localizacion)
        :precondition
            (and
                (en ?u ?x)
                (conectado ?x ?y)
                (tipoUnidad ?u ?t)
                (not (exists (?r - Recurso) (extrayendo ?u ?r)))
            )
        :effect
            (and
                (en ?u ?y)
                (not (en ?u ?x))
                (increase (tiempoTotal) (/ 5 (velocidad ?t)))
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
                (when (tipoRecurso ?r Mineral) (increase (vceExtrayendo Mineral) 1))
                (when (tipoRecurso ?r Gas) (increase (vceExtrayendo Gas) 1))
            )
    )

    (:action Construir
        :parameters (?u - Unidad ?e - Edificio ?t - tipoEdificio ?l - Localizacion)
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

                (tipoEdificio ?e ?t)

                ;Comprobamos que tenemos todos los recursos necesarios
                (forall (?r - tipoRecurso)
                    (imply
                        ;Comprobamos si necesita el recurso ?r
                        (> (necesita ?t ?r) 0)
                        
                        ;Si lo necesita debe estar disponible
                        (>= (recursoDisponible ?r) (necesita ?t ?r))
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
                (when (tipoEdificio ?e Deposito) 
                    (and
                        (increase (maxCapacidad) 100)
                    )
                )
                (when (> (necesita ?t Mineral) 0)
                    (decrease (recursoDisponible Mineral) (necesita ?t Mineral))
                )
                (when (> (necesita ?t Gas) 0)
                    (decrease (recursoDisponible Gas) (necesita ?t Gas))
                )
                (increase (tiempoTotal) (tiempo ?t))
            )
    )

    (:action Reclutar
        :parameters (?u - Unidad ?t - tipoUnidad ?e - Edificio ?l - Localizacion)
        :precondition
            (and
                ;La unidad no ha sido reclutada todavia
                (not (exists (?l2 - Localizacion) (en ?u ?l2)))

                (tipoUnidad ?u ?t)
                (en ?e ?l)

                ;Comprobamos que tenemos todos los recursos necesarios
                (forall (?r - tipoRecurso)
                    (imply
                        ;Comprobamos si necesita el recurso ?r
                        (> (necesita ?t ?r) 0)
                
                        ;Si lo necesita debe estar disponible
                        (>= (recursoDisponible ?r) (necesita ?t ?r))
                    )
                )
                ;Comprobamos que ese tipo de unidad se puede reclutar en ese edificio
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
        :effect
            (and
                (en ?u ?l)
                (when (> (necesita ?t Mineral) 0)
                    (decrease (recursoDisponible Mineral) (necesita ?t Mineral))
                )
                (when (> (necesita ?t Gas) 0)
                    (decrease (recursoDisponible Gas) (necesita ?t Gas))
                )
                (increase (tiempoTotal) (tiempo ?t))
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
                        (> (necesita ?i ?r) 0)
                        ;Si lo necesita debe estar disponible
                        (>= (recursoDisponible ?r) (necesita ?i ?r))
                    )
                )
            )
        :effect
            (and
                (investigado ?i)
                (when (> (necesita ?i Mineral) 0)
                    (decrease (recursoDisponible Mineral) (necesita ?i Mineral)))
                (when (> (necesita ?i Gas) 0)
                    (decrease (recursoDisponible Gas) (necesita ?i Gas)))
                (increase (tiempoTotal) (tiempo ?i))
            )
    )

    (:action Recolectar
        :parameters ()
        :precondition
            (and
                ;No nos pasamos del limite al recolectar
                (<= 
                    (+ (recursoDisponible Mineral) (* (vceExtrayendo Mineral) (cantidadRecolectada)))
                    (maxCapacidad)
                )
                (<= 
                    (+ (recursoDisponible Gas) (* (vceExtrayendo Gas) (cantidadRecolectada)))
                    (maxCapacidad)
                )
            )
        :effect
            (and
                (increase (recursoDisponible Mineral) (* (vceExtrayendo Mineral) (cantidadRecolectada)))
                (increase (recursoDisponible Gas) (* (vceExtrayendo Gas) (cantidadRecolectada)))
                (increase (tiempoTotal) 6)
            )
    )
    (:action Desasignar
        :parameters (?u - Unidad ?r - Recurso)
        :precondition
            (and
                (tipoUnidad ?u VCE)
                (extrayendo ?u ?r)
            )
        :effect
            (and
                (not (extrayendo ?u ?r))
                (when (tipoRecurso ?r Mineral) (decrease (vceExtrayendo Mineral) 1))
                (when (tipoRecurso ?r Gas) (decrease (vceExtrayendo Gas) 1))
            )
    )
)
