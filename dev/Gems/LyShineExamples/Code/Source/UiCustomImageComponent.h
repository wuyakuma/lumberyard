/*
* All or portions of this file Copyright (c) Amazon.com, Inc. or its affiliates or
* its licensors.
*
* For complete copyright and license terms please see the LICENSE at the root of this
* distribution (the "License"). All use of this software is governed by the License,
* or, if provided, by the license below or the license accompanying this file. Do not
* remove or modify any license notices. This file is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
*
*/
#pragma once

#include <LyShine/Bus/UiVisualBus.h>
#include <LyShine/Bus/UiRenderBus.h>
#include <LyShine/UiComponentTypes.h>

#include <LyShineExamples/UiCustomImageBus.h>

#include <AzCore/Component/Component.h>
#include <AzCore/Serialization/SerializeContext.h>
#include <AzCore/Math/Vector2.h>

#include <LmbrCentral/Rendering/MaterialAsset.h>

class ITexture;
class ISprite;

namespace LyShineExamples
{
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    //! This component is an example of how to implement a custom component. It is a simple image
    //! component that takes UV coordinates instead of image and sprite types.
    class UiCustomImageComponent
        : public AZ::Component
        , public UiVisualBus::Handler
        , public UiRenderBus::Handler
        , public UiCustomImageBus::Handler
    {
    public: // member functions

        AZ_COMPONENT(UiCustomImageComponent, "{466B78EC-A85C-4112-A89D-FF2D7EDE650E}", AZ::Component);

        UiCustomImageComponent();
        ~UiCustomImageComponent() override;

        // UiVisualInterface
        void ResetOverrides() override;
        void SetOverrideColor(const AZ::Color& color) override;
        void SetOverrideAlpha(float alpha) override;
        void SetOverrideSprite(ISprite* sprite, AZ::u32 cellIndex = 0) override;
        // ~UiVisualInterface

        // UiRenderInterface
        void Render() override;
        // ~UiRenderInterface

        // UiCustomImageInterface
        AZ::Color GetColor() override;
        void SetColor(const AZ::Color& color) override;
        ISprite* GetSprite() override;
        void SetSprite(ISprite* sprite) override;
        AZStd::string GetSpritePathname() override;
        void SetSpritePathname(AZStd::string spritePath) override;
        UVRect GetUVs() override;
        void SetUVs(UVRect uvs) override;
        bool GetClamp() override;
        void SetClamp(bool clamp) override;
        // ~UiCustomImageInterface

    private: // static member functions

        static void GetProvidedServices(AZ::ComponentDescriptor::DependencyArrayType& provided)
        {
            provided.push_back(AZ_CRC("UiVisualService", 0xa864fdf8));
        }

        static void GetIncompatibleServices(AZ::ComponentDescriptor::DependencyArrayType& incompatible)
        {
            incompatible.push_back(AZ_CRC("UiVisualService", 0xa864fdf8));
        }

        static void GetRequiredServices(AZ::ComponentDescriptor::DependencyArrayType& required)
        {
            required.push_back(AZ_CRC("UiElementService", 0x3dca7ad4));
            required.push_back(AZ_CRC("UiTransformService", 0x3a838e34));
        }

        static void Reflect(AZ::ReflectContext* context);

    private: // member functions

        void RenderSprite(ITexture* texture);
        void RenderSingleQuad(ITexture* texture, const AZ::Vector2* positions, const AZ::Vector2* uvs);
        bool IsPixelAligned();

        void OnSpritePathnameChange();
        // ChangeNotify callback for color change
        void OnColorChange();

        // AZ::Component
        void Init() override;
        void Activate() override;
        void Deactivate() override;
        // ~AZ::Component

        AZ_DISABLE_COPY_MOVE(UiCustomImageComponent);

    private: // data

        AzFramework::SimpleAssetReference<LmbrCentral::TextureAsset> m_spritePathname;
        AZ::Color m_color;
        float m_alpha;
        UVRect m_uvs;
        bool m_clamp;

        ISprite* m_sprite;

        ISprite* m_overrideSprite;
        AZ::Color m_overrideColor;
        float m_overrideAlpha;
    };
}
