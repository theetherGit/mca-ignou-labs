<script lang="ts">
    import { NativeSelect } from "@ethercorps/kit";

    import { onMount } from "svelte";
    let selectedColor = $state("white");
    let demoContainer: HTMLDivElement;

    function setCookie(name: string, value: unknown, days: number) {
        const d = new Date();
        d.setTime(d.getTime() + days * 86400000);
        document.cookie = `${name}=${value};expires=${d.toUTCString()};path=/`;
    }
    function applyColor(color: string) {
        selectedColor = color;
        demoContainer.style.backgroundColor = color;
        setCookie("bgColor", color, 365);
    }

    onMount(() => {
        const match = document.cookie.match(/bgColor=([^;]+)/);
        if (match) applyColor(match[1]);
    });
</script>

<div
    bind:this={demoContainer}
    class="p-8 min-h-auto text-black rounded-xl mt-5 flex flex-col items-center justify-center gap-4 transition-colors duration-300"
>
    <h3
        class="text-lg font-semibold text-gray-800 bg-white/80 px-4 py-2 rounded-lg backdrop-blur-sm"
    >
        Select Background Color (Persisted via Cookie)
    </h3>
    <NativeSelect
        bind:value={selectedColor}
        onchange={(e) => applyColor(selectedColor)}
    >
        <option value="white">White</option>
        <option value="#fef08a">Yellow</option>
        <option value="#86efac">Green</option>
        <option value="#93c5fd">Blue</option>
        <option value="#d8b4fe">Purple</option>
    </NativeSelect>
    <p class="text-sm text-gray-600 bg-white/70 px-3 py-1 rounded">
        Current: {selectedColor}
    </p>
</div>
