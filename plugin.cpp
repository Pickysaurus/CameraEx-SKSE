//using RE::NiPoint3;
//
//void LookAtInstant(RE::TESObjectREFR* a_target, float a_strength) {
//    if (!a_target) {
//        return;
//    }
//
//    auto* player = RE::PlayerCharacter::GetSingleton();
//    if (!player) {
//        return;
//    }
//
//    auto* camera = RE::PlayerCamera::GetSingleton();
//    if (!camera) {
//        return;
//    }
//
//    // Make sure we're in 3rd-person so ThirdPersonState is active
//    camera->ForceThirdPerson();
//
//    // Get current third-person camera state
//    auto* state = camera->currentState.get();
//    auto* tp = state ? static_cast<RE::ThirdPersonState*>(state) : nullptr;
//    if (!tp) {
//        // Not in a third-person state we know how to handle
//        return;
//    }
//
//    // --- Compute eye position ---
//    NiPoint3 eyePos{};
//    {
//        // Simple eye approximation: position + height * factor
//        eyePos = player->GetPosition();
//        eyePos.z += player->GetHeight() * 0.9f;
//    }
//
//    const NiPoint3 targetPos = a_target->GetPosition();
//
//    NiPoint3 dir;
//    dir.x = targetPos.x - eyePos.x;
//    dir.y = targetPos.y - eyePos.y;
//    dir.z = targetPos.z - eyePos.z;
//
//    const float lenSq = dir.x * dir.x + dir.y * dir.y + dir.z * dir.z;
//    if (lenSq < 1e-8f) {
//        return;
//    }
//
//    const float len = std::sqrt(lenSq);
//    dir.x /= len;
//    dir.y /= len;
//    dir.z /= len;
//
//    // --- Desired yaw/pitch in *radians* ---
//    // Yaw: around Z, looking down onto X/Y plane
//    float targetYaw = std::atan2(dir.x, dir.y);
//    // Pitch: up/down, using Z
//    float targetPitch = std::asin(dir.z);
//
//    // Clamp blend strength
//    float t = std::clamp(a_strength, 0.0f, 1.0f);
//
//    // --- Blend yaw using ThirdPersonState’s yaw values ---
//    float curYaw = tp->currentYaw;  // In radians
//    float newYaw = std::lerp(curYaw, targetYaw, t);
//
//    tp->currentYaw = newYaw;
//    tp->targetYaw = newYaw;
//
//    // --- Blend pitch via freeRotation (NiPoint2) ---
//    // Convention: freeRotation.x = pitch, freeRotation.y = yaw (radians)
//    RE::NiPoint2 fr = tp->freeRotation;
//    fr.x = std::lerp(fr.x, targetPitch, t);  // pitch
//    fr.y = newYaw;                           // yaw
//    tp->freeRotation = fr;
//    tp->freeRotationEnabled = true;
//
//    // Recompute internal quaternion/etc based on updated yaw/pitch
//    tp->UpdateRotation();
//}
//
//static bool LookAt(RE::StaticFunctionTag*, RE::TESObjectREFR* a_target, float a_strength) {
//    if (!a_target) {
//        return false;
//    }
//    if (a_strength <= 0.0f) {
//        a_strength = 1.0f;
//    } else if (a_strength > 1.0f) {
//        a_strength = 1.0f;
//    }
//
//    LookAtInstant(a_target, a_strength);
//    return true;
//}
//
//
//bool BindPapyrusFunction(RE::BSScript::IVirtualMachine* vm) { 
//    vm->RegisterFunction("LookAt", "CameraEx", LookAt);
//    return true;
//}

bool registered = false;

SKSEPluginLoad(const SKSE::LoadInterface *skse) {
    // InitializeLogging();
    SKSE::Init(skse);

    //auto papyrus = SKSE::GetPapyrusInterface();
    //registered = papyrus->Register(BindPapyrusFunction);

    // This example prints "Hello, world!" to the Skyrim ~ console.
    // To view it, open the ~ console from the Skyrim Main Menu.
    SKSE::GetMessagingInterface()->RegisterListener([](SKSE::MessagingInterface::Message *message) {
        if (message->type == SKSE::MessagingInterface::kDataLoaded)
            RE::ConsoleLog::GetSingleton()->Print("Hello, world! CameraEx loaded");            
    });

    return true;
}