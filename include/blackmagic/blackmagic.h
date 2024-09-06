#pragma once

/**
 * @file
 * Include all blackmagic headers with a single include
 * @author Antoine GAGNIERE
 */

#include "blackmagic/color.h"
#include "blackmagic/enum.h"
#include "blackmagic/fold.h"
#include "blackmagic/for.h"
#include "blackmagic/log.h"
#include "blackmagic/token.h"

/**
 * @dir include
 * This directory is what shall be added to the search path for headers.
 * That way it will be explicit that a blackmagic header is being included, as it will look like:
 * @code{.c}
 * #include <blackmagic/foo.h>
 * @endcode
 * @author Antoine GAGNIERE
 */

/**
 * @dir blackmagic
 * This directory contains all blackmagic headers.
 * Do not add it directly to the search path for headers, prefer instead the `include` directory
 * @author Antoine GAGNIERE
 */

/**
 * @mainpage
 * Welcome to the documentation of black magic.
 * @author Antoine GAGNIERE
 */
