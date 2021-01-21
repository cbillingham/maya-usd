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
#include "sessionState.h"

namespace UsdLayerEditor {

void SessionState::setAutoHideSessionLayer(bool hideIt)
{
    _autoHideSessionLayer = hideIt;
    Q_EMIT autoHideSessionLayerSignal(_autoHideSessionLayer);
}

void SessionState::setStage(PXR_NS::UsdStageRefPtr const& in_stage)
{
    if (in_stage != _stage) {
        _stage = in_stage;
        Q_EMIT currentStageChangedSignal();
    }
}

PXR_NS::SdfLayerRefPtr SessionState::targetLayer() const
{
    if (_stage != nullptr) {
        const auto& target = _stage->GetEditTarget();
        return target.GetLayer();
    } else {
        return nullptr;
    }
}

} // namespace UsdLayerEditor