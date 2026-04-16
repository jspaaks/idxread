#include "idx/idx.h"
#include "cla/cla.h"
#include <errno.h>       // errno
#include <inttypes.h>    // PRIi8, PRIi16, PRIi32, PRIu8
#include <limits.h>      // INT_MAX
#include <stdio.h>       // stdout, perror
#include <stdint.h>      // int8_t, int16_t, int32_t, uint8_t
#include <stdlib.h>      // EXIT_FAILURE, EXIT_SUCCESS
#include <string.h>      // 
#include <sys/param.h>   // MIN, MAX

typedef void (*Strategy)(IdxFileObject * idx, FILE * stream, int ifrom, int ito, int ncolumns);

static void assert_meta_is_only_option (struct cla * cla, int argc);
static void assert_nhead_and_ntail_mutually_exclusive (struct cla * cla);
static int get_ncolumns (struct cla * cla, int default_value);
static int get_nhead (struct cla * cla, int default_value);
static int get_ntail (struct cla * cla, int default_value);
static void show_meta (const struct idx_file_object * idx, const char * filepath, FILE * stream);
static void show_usage (FILE * stream, const char * programname);
static void strat_double (IdxFileObject * idx, FILE * stream, int ifrom, int ito, int ncolumns);
static void strat_float (IdxFileObject * idx, FILE * stream, int ifrom, int ito, int ncolumns);
static void strat_int8 (IdxFileObject * idx, FILE * stream, int ifrom, int ito, int ncolumns);
static void strat_int16 (IdxFileObject * idx, FILE * stream, int ifrom, int ito, int ncolumns);
static void strat_int32 (IdxFileObject * idx, FILE * stream, int ifrom, int ito, int ncolumns);
static void strat_uint8 (IdxFileObject * idx, FILE * stream, int ifrom, int ito, int ncolumns);


static void assert_meta_is_only_option (struct cla * cla, int argc) {
    if (!CLA_has_flag(cla, "--meta")) {
        fprintf(stderr, "Expected '--meta|-m' flag but didn't find it, aborting.\n");
        exit(EXIT_FAILURE);
    }
    if (argc != 3) {
        fprintf(stderr, "Use of '--meta|-m' precludes all other options, aborting.\n");
        exit(EXIT_FAILURE);
    }
}


static void assert_nhead_and_ntail_mutually_exclusive (struct cla * cla) {
    if (CLA_has_optional(cla, "--nhead") && CLA_has_optional(cla, "--ntail")) {
        fprintf(stderr, "Options '--nhead' and '--ntail|-t' are mutually exclusive, aborting.\n");
        exit(EXIT_FAILURE);
    }
}


static int get_ncolumns (struct cla * cla, int default_value) {
    if (!CLA_has_optional(cla, "--ncolumns")) {
        return default_value;
    }
    const char * ncolumns_s = CLA_get_value_optional(cla, "--ncolumns");
    char * endptr = nullptr;
    const int base = 10;
    errno = 0;
    long parsed = strtol(ncolumns_s, &endptr, base);
    if (errno == ERANGE) {
        perror("Error parsing value of --ncolumns");
        exit(EXIT_FAILURE);
    }
    if (endptr == ncolumns_s) {
        fprintf(stderr, "No digits were found while parsing '--ncolumns' argument (%s), aborting\n", ncolumns_s);
        exit(EXIT_FAILURE);
    }
    if (*endptr != '\0') {
        fprintf(stderr, "Trailing characters found when parsing value of '--ncolumns' argument (%s), aborting\n", ncolumns_s);
        exit(EXIT_FAILURE);
    }
    if (parsed <= 0) {
        fprintf(stderr, "--ncolumns argument should be at least 1 but found %ld, aborting\n", parsed);
        exit(EXIT_FAILURE);
    }
    if (parsed > INT_MAX) {
        fprintf(stderr, "--ncolumns argument should be less then %d but found %ld, aborting\n", INT_MAX, parsed);
        exit(EXIT_FAILURE);
    }
    return (int) parsed;
}


static int get_nhead (struct cla * cla, int default_value) {
    if (!CLA_has_optional(cla, "--nhead")) {
        return default_value;
    }
    const char * nhead_s = CLA_get_value_optional(cla, "--nhead");
    char * endptr = nullptr;
    const int base = 10;
    errno = 0;
    long parsed = strtol(nhead_s, &endptr, base);
    if (errno == ERANGE) {
        perror("Error parsing value of --nhead");
        exit(EXIT_FAILURE);
    }
    if (endptr == nhead_s) {
        fprintf(stderr, "No digits were found while parsing '--nhead' argument (%s), aborting\n", nhead_s);
        exit(EXIT_FAILURE);
    }
    if (*endptr != '\0') {
        fprintf(stderr, "Trailing characters found when parsing value of '--nhead' argument (%s), aborting\n", nhead_s);
        exit(EXIT_FAILURE);
    }
    if (parsed <= 0) {
        fprintf(stderr, "--nhead argument should be at least 1 but found %ld, aborting\n", parsed);
    }
    if (parsed > INT_MAX) {
        fprintf(stderr, "--nhead argument should be less than %d but found %ld, aborting\n", INT_MAX, parsed);
    }
    return (int) parsed;
}


static int get_ntail (struct cla * cla, int default_value) {
    if (!CLA_has_optional(cla, "--ntail")) {
        return default_value;
    }
    const char * ntail_s = CLA_get_value_optional(cla, "--ntail");
    char * endptr = nullptr;
    const int base = 10;
    errno = 0;
    long parsed = strtol(ntail_s, &endptr, base);
    if (errno == ERANGE) {
        perror("Error parsing value of --ntail|-t");
        exit(EXIT_FAILURE);
    }
    if (endptr == ntail_s) {
        fprintf(stderr, "No digits were found while parsing '--ntail' argument (%s), aborting\n", ntail_s);
        exit(EXIT_FAILURE);
    }
    if (*endptr != '\0') {
        fprintf(stderr, "Trailing characters found when parsing value of '--ntail' argument (%s), aborting\n", ntail_s);
        exit(EXIT_FAILURE);
    }
    if (parsed <= 0) {
        fprintf(stderr, "--ntail argument should be at least 1 but found %ld, aborting\n", parsed);
    }
    if (parsed > INT_MAX) {
        fprintf(stderr, "--ntail argument should be less than %d but found %ld, aborting\n", INT_MAX, parsed);
    }
    return (int) parsed;
}


int main (const int argc, const char * argv[]) {
    struct cla * cla = CLA_create();
    CLA_add_flag(cla, "--meta", "-m");
    CLA_add_optional(cla, "--ncolumns", "-c");
    CLA_add_optional(cla, "--nhead", nullptr);
    CLA_add_optional(cla, "--ntail", "-t");
    CLA_add_positionals(cla, 1);
    CLA_parse(cla, argc, argv);

    if (CLA_help_requested(cla)) {
        show_usage(stdout, argv[0]);
        CLA_destroy(&cla);
        exit(EXIT_SUCCESS);
    }

    const char * filepath = CLA_get_value_positional(cla, 0);
    IdxFileObject * idx = idx_create(filepath);
    idx_read_meta(idx);

    if (CLA_has_flag(cla, "--meta")) {
        assert_meta_is_only_option(cla, argc);
        show_meta(idx, filepath, stdout);
        idx_destroy(&idx);
        CLA_destroy(&cla);
        return EXIT_SUCCESS;
    }

    assert_nhead_and_ntail_mutually_exclusive (cla);

    int nelems = idx_get_nelems(idx);
    int ncolumns = get_ncolumns(cla, nelems);
    int nhead = get_nhead(cla, nelems);
    int ntail = get_ntail(cla, nelems);

    int ifrom = MAX(nelems - ntail, 0);
    int ito = MIN(nhead, nelems);

    idx_read_body(idx);
    IdxDataType t = idx_get_type(idx);
    const Strategy strategies[IDX_DATA_TYPE_DOUBLE + 1] = {
        [IDX_DATA_TYPE_UINT8] = strat_uint8,
        [IDX_DATA_TYPE_INT8] = strat_int8,
        [IDX_DATA_TYPE_INT16] = strat_int16,
        [IDX_DATA_TYPE_INT32] = strat_int32,
        [IDX_DATA_TYPE_FLOAT] = strat_float,
        [IDX_DATA_TYPE_DOUBLE] = strat_double
    };
    strategies[t](idx, stdout, ifrom, ito, ncolumns);
    idx_destroy(&idx);
    CLA_destroy(&cla);
    return EXIT_SUCCESS;
}


static void show_meta (const struct idx_file_object * idx, const char * filepath, FILE * stream) {
    uint8_t type = (uint8_t) idx_get_type(idx);
    uint8_t ndims = idx_get_ndims_raw(idx);
    size_t nelems = idx_get_nelems_raw(idx);
    const char * type_name = idx_get_type_name(idx);
    fprintf(stream, "path              : %s\n", filepath);
    fprintf(stream, "type              : 0x%02hhx (%s)\n", type, type_name);
    fprintf(stream, "ndims             : %hhu \n", ndims);
    fprintf(stream, "dimension lengths : ");
    for (int idim = 0; idim < ndims; idim++) {
        char c = idim % 10 == 9 ? '\n' : ' ';
        uint32_t length = idx_get_dim_length_raw(idx, idim);
        fprintf(stream, "%" PRIu32 "%c", length, c);
    }
    fprintf(stream, "\n");
    fprintf(stream, "number of elements: %zu\n", nelems);
}


static void show_usage (FILE * stream, const char * programname) {
    fprintf(stream,
            "Usage: %s [--help|-h]\n"
            "Usage: %s [--meta|-m] FILEPATH\n"
            "Usage: %s [OPTIONS] FILEPATH\n"
            "\n"
            "    Read IDX-formatted data from a binary file located at FILEPATH.\n"
            "\n"
            "    Options\n"
            "\n"
            "    --nhead NELEMS\n"
            "\n"
            "        Show the first NELEMS elements of the data in FILEPATH\n"
            "\n"
            "    --meta, -m\n"
            "\n"
            "        Show the metadata of the data in FILEPATH\n"
            "\n"
            "    --ncolumns, -c NCOLUMNS\n"
            "\n"
            "        Print the data using NCOLUMNS columns\n"
            "\n"
            "    --ntail, -t NELEMS\n"
            "\n"
            "        Show the last NELEMS elements of the data in FILEPATH\n"
            "\n", programname, programname, programname);
}


static void strat_double (IdxFileObject * idx, FILE * stream, int ifrom, int ito, int ncolumns) {
    const double * buf = idx_get_data_double(idx);
    for (int i = ifrom; i < ito; i++) {
        bool a = (i - ifrom) % ncolumns == ncolumns - 1;
        bool b = i == ito - 1;
        char ch = a || b ? '\n' : ' ';
        fprintf(stream, "%11.4g%c", buf[i], ch);
    }
}


static void strat_float (IdxFileObject * idx, FILE * stream, int ifrom, int ito, int ncolumns) {
    const float * buf = idx_get_data_float(idx);
    for (int i = ifrom; i < ito; i++) {
        bool a = (i - ifrom) % ncolumns == ncolumns - 1;
        bool b = i == ito - 1;
        char ch = a || b ? '\n' : ' ';
        fprintf(stream, "%10.4g%c", buf[i], ch);
    }
}


static void strat_int8 (IdxFileObject * idx, FILE * stream, int ifrom, int ito, int ncolumns) {
    const int8_t * buf = idx_get_data_int8(idx);
    for (int i = ifrom; i < ito; i++) {
        bool a = (i - ifrom) % ncolumns == ncolumns - 1;
        bool b = i == ito - 1;
        char ch = a || b ? '\n' : ' ';
        fprintf(stream, "%4" PRIi8 "%c", buf[i], ch);
    }
}


static void strat_int16 (IdxFileObject * idx, FILE * stream, int ifrom, int ito, int ncolumns) {
    const int16_t * buf = idx_get_data_int16(idx);
    for (int i = ifrom; i < ito; i++) {
        bool a = (i - ifrom) % ncolumns == ncolumns - 1;
        bool b = i == ito - 1;
        char ch = a || b ? '\n' : ' ';
        fprintf(stream, "%6" PRIi16 "%c", buf[i], ch);
    }
}


static void strat_int32 (IdxFileObject * idx, FILE * stream, int ifrom, int ito, int ncolumns) {
    const int32_t * buf = idx_get_data_int32(idx);
    for (int i = ifrom; i < ito; i++) {
        bool a = (i - ifrom) % ncolumns == ncolumns - 1;
        bool b = i == ito - 1;
        char ch = a || b ? '\n' : ' ';
        fprintf(stream, "%11" PRIi32 "%c", buf[i], ch);
    }
}


static void strat_uint8 (IdxFileObject * idx, FILE * stream, int ifrom, int ito, int ncolumns) {
    const uint8_t * buf = idx_get_data_uint8(idx);
    for (int i = ifrom; i < ito; i++) {
        bool a = (i - ifrom) % ncolumns == ncolumns - 1;
        bool b = i == ito - 1;
        char ch = a || b ? '\n' : ' ';
        fprintf(stream, "%3" PRIu8 "%c", buf[i], ch);
    }
}
