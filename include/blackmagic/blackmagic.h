#pragma once

/**
 * @file
 * Include all blackmagic headers with a single include
 */

#include "blockmagic/token.h"
#include "blockmagic/log.h"
#include "blockmagic/for.h"
#include "blockmagic/color.h"
#include "blockmagic/enum.h"
#include "blackmagic/fold.h"

/**
 * @dir include
 * This directory is what shall be added to the search path for headers.
 * That way it will be explicit that a blackmagic header is being included, as it will look like:
 * @code{.c}
 * #include <blackmagic/foo.h>
 * @endcode
 */

/**
 * @dir blackmagic
 * This directory contains all blackmagic headers.
 * Do not add it directly to the search path for headers, prefer instead the `include` directory
 */

/**
 * @mainpage
 * Welcome to the documentation of black magic.
 */
