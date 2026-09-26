<script lang="ts">
    let time = $state("00:00:00");

    function formatTime(date: Date) {
        return [date.getHours(), date.getMinutes(), date.getSeconds()]
            .map((n) => String(n).padStart(2, "0"))
            .join(":");
    }

    // Initialize interval
    setInterval(() => {
        time = formatTime(new Date());
    }, 1000);
    time = formatTime(new Date());
</script>

<div
    class="min-h-auto text-black mt-5 rounded-xl bg-gray-900 flex flex-col items-center justify-center gap-4"
>
    <h1 class="text-2xl font-semibold text-gray-200">Live Clock</h1>
    <div
        class="text-6xl font-mono font-bold tracking-widest text-cyan-400 drop-shadow-lg"
    >
        {time}
    </div>
    <p class="text-gray-400 text-sm">Updates every second via setInterval()</p>
</div>
