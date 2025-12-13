--
-- PostgreSQL database dump
--

\restrict XX3YV2TfXWd6isfaqVlUdbK7gwXbVRuswVa1uj1b9XKVXP8oBR6CdLYnauigQ3S

-- Dumped from database version 17.6
-- Dumped by pg_dump version 17.6

-- Started on 2025-12-06 22:10:28

SET statement_timeout = 0;
SET lock_timeout = 0;
SET idle_in_transaction_session_timeout = 0;
SET transaction_timeout = 0;
SET client_encoding = 'UTF8';
SET standard_conforming_strings = on;
SELECT pg_catalog.set_config('search_path', '', false);
SET check_function_bodies = false;
SET xmloption = content;
SET client_min_messages = warning;
SET row_security = off;

SET default_tablespace = '';

SET default_table_access_method = heap;

--
-- TOC entry 228 (class 1259 OID 32897)
-- Name: authorship; Type: TABLE; Schema: public; Owner: postgres
--

CREATE TABLE public.authorship (
    authorship_id integer NOT NULL,
    researcher_id integer NOT NULL,
    publication_id integer NOT NULL,
    role character varying(50) NOT NULL
);


ALTER TABLE public.authorship OWNER TO postgres;

--
-- TOC entry 227 (class 1259 OID 32896)
-- Name: authorship_authorship_id_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

ALTER TABLE public.authorship ALTER COLUMN authorship_id ADD GENERATED ALWAYS AS IDENTITY (
    SEQUENCE NAME public.authorship_authorship_id_seq
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1
);


--
-- TOC entry 220 (class 1259 OID 32849)
-- Name: discipline; Type: TABLE; Schema: public; Owner: postgres
--

CREATE TABLE public.discipline (
    discipline_id integer NOT NULL,
    name character varying(50) NOT NULL,
    code character varying(50) NOT NULL,
    description text NOT NULL
);


ALTER TABLE public.discipline OWNER TO postgres;

--
-- TOC entry 219 (class 1259 OID 32848)
-- Name: discipline_discipline_id_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

ALTER TABLE public.discipline ALTER COLUMN discipline_id ADD GENERATED ALWAYS AS IDENTITY (
    SEQUENCE NAME public.discipline_discipline_id_seq
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1
);


--
-- TOC entry 226 (class 1259 OID 32885)
-- Name: file; Type: TABLE; Schema: public; Owner: postgres
--

CREATE TABLE public.file (
    file_id integer NOT NULL,
    publication_id integer NOT NULL,
    file_name character varying(50) NOT NULL,
    format character varying(50) NOT NULL,
    size integer NOT NULL,
    upload_date timestamp without time zone DEFAULT now() NOT NULL
);


ALTER TABLE public.file OWNER TO postgres;

--
-- TOC entry 225 (class 1259 OID 32884)
-- Name: file_file_id_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

ALTER TABLE public.file ALTER COLUMN file_id ADD GENERATED ALWAYS AS IDENTITY (
    SEQUENCE NAME public.file_file_id_seq
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1
);


--
-- TOC entry 222 (class 1259 OID 32857)
-- Name: license; Type: TABLE; Schema: public; Owner: postgres
--

CREATE TABLE public.license (
    license_id integer NOT NULL,
    license_name character varying(50) NOT NULL,
    access_type character varying(50) NOT NULL,
    price numeric(50,2) DEFAULT 0 NOT NULL,
    description text NOT NULL
);


ALTER TABLE public.license OWNER TO postgres;

--
-- TOC entry 221 (class 1259 OID 32856)
-- Name: license_license_id_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

ALTER TABLE public.license ALTER COLUMN license_id ADD GENERATED ALWAYS AS IDENTITY (
    SEQUENCE NAME public.license_license_id_seq
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1
);


--
-- TOC entry 224 (class 1259 OID 32866)
-- Name: publication; Type: TABLE; Schema: public; Owner: postgres
--

CREATE TABLE public.publication (
    publication_id integer NOT NULL,
    discipline_id integer NOT NULL,
    license_id integer NOT NULL,
    title character varying(255) NOT NULL,
    abstract text NOT NULL,
    publish_date date NOT NULL,
    version integer DEFAULT 1 NOT NULL,
    doi character varying(50) NOT NULL
);


ALTER TABLE public.publication OWNER TO postgres;

--
-- TOC entry 223 (class 1259 OID 32865)
-- Name: publication_publication_id_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

ALTER TABLE public.publication ALTER COLUMN publication_id ADD GENERATED ALWAYS AS IDENTITY (
    SEQUENCE NAME public.publication_publication_id_seq
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1
);


--
-- TOC entry 218 (class 1259 OID 32843)
-- Name: researcher; Type: TABLE; Schema: public; Owner: postgres
--

CREATE TABLE public.researcher (
    researcher_id integer NOT NULL,
    first_name character varying(50) NOT NULL,
    last_name character varying(50) NOT NULL,
    degree character varying(50) NOT NULL,
    email character varying(50) NOT NULL
);


ALTER TABLE public.researcher OWNER TO postgres;

--
-- TOC entry 217 (class 1259 OID 32842)
-- Name: researcher_researcher_id_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

ALTER TABLE public.researcher ALTER COLUMN researcher_id ADD GENERATED ALWAYS AS IDENTITY (
    SEQUENCE NAME public.researcher_researcher_id_seq
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1
);


--
-- TOC entry 4896 (class 0 OID 32897)
-- Dependencies: 228
-- Data for Name: authorship; Type: TABLE DATA; Schema: public; Owner: postgres
--

COPY public.authorship (authorship_id, researcher_id, publication_id, role) FROM stdin;
1	1	1	Головний автор
2	2	1	Рецензент
\.


--
-- TOC entry 4888 (class 0 OID 32849)
-- Dependencies: 220
-- Data for Name: discipline; Type: TABLE DATA; Schema: public; Owner: postgres
--

COPY public.discipline (discipline_id, name, code, description) FROM stdin;
1	Комп'ютерні науки	122	Штучний інтелект та бази даних
2	Прикладна математика	113	Математичне моделювання
\.


--
-- TOC entry 4894 (class 0 OID 32885)
-- Dependencies: 226
-- Data for Name: file; Type: TABLE DATA; Schema: public; Owner: postgres
--

COPY public.file (file_id, publication_id, file_name, format, size, upload_date) FROM stdin;
1	1	research_paper.pdf	pdf	102400	2025-12-06 21:09:31.454373
\.


--
-- TOC entry 4890 (class 0 OID 32857)
-- Dependencies: 222
-- Data for Name: license; Type: TABLE DATA; Schema: public; Owner: postgres
--

COPY public.license (license_id, license_name, access_type, price, description) FROM stdin;
1	CC-BY 4.0	Відкритий	0.00	Вільне використання з атрибуцією
2	Copyright	Закритий	50.00	Всі права захищено
\.


--
-- TOC entry 4892 (class 0 OID 32866)
-- Dependencies: 224
-- Data for Name: publication; Type: TABLE DATA; Schema: public; Owner: postgres
--

COPY public.publication (publication_id, discipline_id, license_id, title, abstract, publish_date, version, doi) FROM stdin;
1	1	1	Оптимізація SQL запитів	Аналіз продуктивності баз даних PostgreSQL...	2023-11-01	1	10.1000/sql-opt
\.


--
-- TOC entry 4886 (class 0 OID 32843)
-- Dependencies: 218
-- Data for Name: researcher; Type: TABLE DATA; Schema: public; Owner: postgres
--

COPY public.researcher (researcher_id, first_name, last_name, degree, email) FROM stdin;
1	Олександр	Ковальчук	Доктор наук	kovalchuk@science.org
2	Ірина	Мельник	Аспірант	i.melnyk@uni.edu.ua
\.


--
-- TOC entry 4902 (class 0 OID 0)
-- Dependencies: 227
-- Name: authorship_authorship_id_seq; Type: SEQUENCE SET; Schema: public; Owner: postgres
--

SELECT pg_catalog.setval('public.authorship_authorship_id_seq', 2, true);


--
-- TOC entry 4903 (class 0 OID 0)
-- Dependencies: 219
-- Name: discipline_discipline_id_seq; Type: SEQUENCE SET; Schema: public; Owner: postgres
--

SELECT pg_catalog.setval('public.discipline_discipline_id_seq', 2, true);


--
-- TOC entry 4904 (class 0 OID 0)
-- Dependencies: 225
-- Name: file_file_id_seq; Type: SEQUENCE SET; Schema: public; Owner: postgres
--

SELECT pg_catalog.setval('public.file_file_id_seq', 1, true);


--
-- TOC entry 4905 (class 0 OID 0)
-- Dependencies: 221
-- Name: license_license_id_seq; Type: SEQUENCE SET; Schema: public; Owner: postgres
--

SELECT pg_catalog.setval('public.license_license_id_seq', 2, true);


--
-- TOC entry 4906 (class 0 OID 0)
-- Dependencies: 223
-- Name: publication_publication_id_seq; Type: SEQUENCE SET; Schema: public; Owner: postgres
--

SELECT pg_catalog.setval('public.publication_publication_id_seq', 1, true);


--
-- TOC entry 4907 (class 0 OID 0)
-- Dependencies: 217
-- Name: researcher_researcher_id_seq; Type: SEQUENCE SET; Schema: public; Owner: postgres
--

SELECT pg_catalog.setval('public.researcher_researcher_id_seq', 2, true);


--
-- TOC entry 4734 (class 2606 OID 32901)
-- Name: authorship authorship_pkey; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.authorship
    ADD CONSTRAINT authorship_pkey PRIMARY KEY (authorship_id);


--
-- TOC entry 4726 (class 2606 OID 32855)
-- Name: discipline discipline_pkey; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.discipline
    ADD CONSTRAINT discipline_pkey PRIMARY KEY (discipline_id);


--
-- TOC entry 4732 (class 2606 OID 32890)
-- Name: file file_pkey; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.file
    ADD CONSTRAINT file_pkey PRIMARY KEY (file_id);


--
-- TOC entry 4728 (class 2606 OID 32864)
-- Name: license license_pkey; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.license
    ADD CONSTRAINT license_pkey PRIMARY KEY (license_id);


--
-- TOC entry 4730 (class 2606 OID 32873)
-- Name: publication publication_pkey; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.publication
    ADD CONSTRAINT publication_pkey PRIMARY KEY (publication_id);


--
-- TOC entry 4724 (class 2606 OID 32847)
-- Name: researcher researcher_pkey; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.researcher
    ADD CONSTRAINT researcher_pkey PRIMARY KEY (researcher_id);


--
-- TOC entry 4738 (class 2606 OID 32907)
-- Name: authorship authorship_publication_fkey; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.authorship
    ADD CONSTRAINT authorship_publication_fkey FOREIGN KEY (publication_id) REFERENCES public.publication(publication_id);


--
-- TOC entry 4739 (class 2606 OID 32902)
-- Name: authorship authorship_researcher_fkey; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.authorship
    ADD CONSTRAINT authorship_researcher_fkey FOREIGN KEY (researcher_id) REFERENCES public.researcher(researcher_id);


--
-- TOC entry 4737 (class 2606 OID 32891)
-- Name: file file_publication_fkey; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.file
    ADD CONSTRAINT file_publication_fkey FOREIGN KEY (publication_id) REFERENCES public.publication(publication_id);


--
-- TOC entry 4735 (class 2606 OID 32874)
-- Name: publication publication_discipline_fkey; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.publication
    ADD CONSTRAINT publication_discipline_fkey FOREIGN KEY (discipline_id) REFERENCES public.discipline(discipline_id);


--
-- TOC entry 4736 (class 2606 OID 32879)
-- Name: publication publication_license_fkey; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.publication
    ADD CONSTRAINT publication_license_fkey FOREIGN KEY (license_id) REFERENCES public.license(license_id);


-- Completed on 2025-12-06 22:10:28

--
-- PostgreSQL database dump complete
--

\unrestrict XX3YV2TfXWd6isfaqVlUdbK7gwXbVRuswVa1uj1b9XKVXP8oBR6CdLYnauigQ3S

