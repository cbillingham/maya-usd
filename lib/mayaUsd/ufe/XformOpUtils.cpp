//
// Copyright 2020 Autodesk
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//

#include "XformOpUtils.h"

#include <pxr/usd/usdGeom/xformable.h>

namespace MAYAUSD_NS_DEF {
namespace ufe {

template <bool INCLUSIVE>
GfMatrix4d computeLocalTransform(
    const std::vector<UsdGeomXformOp>&          ops,
    std::vector<UsdGeomXformOp>::const_iterator endOp,
    const UsdTimeCode&                          time)
{
    // If we want the op to be included, increment the end op iterator.
    if (INCLUSIVE) {
        TF_AXIOM(endOp != ops.end());
        ++endOp;
    }

    // GetLocalTransformation() interface does not allow passing a begin and
    // end iterator, so copy into an argument vector.
    std::vector<UsdGeomXformOp> argOps(std::distance(ops.begin(), endOp));
    argOps.assign(ops.begin(), endOp);

    GfMatrix4d m(1);
    if (!UsdGeomXformable::GetLocalTransformation(&m, argOps, time)) {
        TF_FATAL_ERROR("Local transformation computation failed.");
    }

    return m;
}

template GfMatrix4d computeLocalTransform<true>(
    const std::vector<UsdGeomXformOp>&          ops,
    std::vector<UsdGeomXformOp>::const_iterator endOp,
    const UsdTimeCode&                          time
);
template GfMatrix4d computeLocalTransform<false>(
    const std::vector<UsdGeomXformOp>&          ops,
    std::vector<UsdGeomXformOp>::const_iterator endOp,
    const UsdTimeCode&                          time
);

std::vector<UsdGeomXformOp> getOrderedXformOps(const UsdPrim& prim)
{
    UsdGeomXformable xformable(prim);
    bool unused;
    return xformable.GetOrderedXformOps(&unused);
}

} // namespace ufe
} // namespace MAYAUSD_NS_DEF
