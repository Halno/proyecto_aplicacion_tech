--
-- PostgreSQL database dump
--

-- Dumped from database version 10.10
-- Dumped by pg_dump version 10.10

SET statement_timeout = 0;
SET lock_timeout = 0;
SET idle_in_transaction_session_timeout = 0;
SET client_encoding = 'UTF8';
SET standard_conforming_strings = on;
SELECT pg_catalog.set_config('search_path', '', false);
SET check_function_bodies = false;
SET xmloption = content;
SET client_min_messages = warning;
SET row_security = off;

SET default_tablespace = '';

SET default_with_oids = false;

--
-- Name: entrada; Type: TABLE; Schema: public; Owner: postgres
--

CREATE TABLE public.entrada (
    id_entrada integer NOT NULL,
    id_usuario_entrada integer NOT NULL,
    contenido_entrada text NOT NULL,
    personaje character varying(20) NOT NULL
);


ALTER TABLE public.entrada OWNER TO postgres;

--
-- Name: entrada_id_entrada_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE public.entrada_id_entrada_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public.entrada_id_entrada_seq OWNER TO postgres;

--
-- Name: entrada_id_entrada_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE public.entrada_id_entrada_seq OWNED BY public.entrada.id_entrada;


--
-- Name: entrada id_entrada; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.entrada ALTER COLUMN id_entrada SET DEFAULT nextval('public.entrada_id_entrada_seq'::regclass);


--
-- Data for Name: entrada; Type: TABLE DATA; Schema: public; Owner: postgres
--

COPY public.entrada (id_entrada, id_usuario_entrada, contenido_entrada, personaje) FROM stdin;
6	8	Después de conseguir un knockdown con Spiral Arrow, puedes hacer un setup anti-DP haciendo la versión M de Hooligan Combination.	cammy
12	8	No hagas Tatsu Fuerte en neutro, es -4 en block.	ken
13	8	Puedes cancelar fStMK con un especial para avanzar, por ejemplo, antes de hacer un Tiger Uppercut.	sagat
15	14	Puedes aturdir con el CA si te encuentras en V-Trigger 1	ryu
\.


--
-- Name: entrada_id_entrada_seq; Type: SEQUENCE SET; Schema: public; Owner: postgres
--

SELECT pg_catalog.setval('public.entrada_id_entrada_seq', 18, true);


--
-- Name: entrada entrada_pkey; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.entrada
    ADD CONSTRAINT entrada_pkey PRIMARY KEY (id_entrada);


--
-- Name: entrada entrada_id_usuario_entrada_fkey; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.entrada
    ADD CONSTRAINT entrada_id_usuario_entrada_fkey FOREIGN KEY (id_usuario_entrada) REFERENCES public.usuario(id_usuario);


--
-- PostgreSQL database dump complete
--

